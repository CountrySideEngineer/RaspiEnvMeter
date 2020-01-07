#ifndef CGPIO_H
#define CGPIO_H
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <QObject>
#include <QTime>
#include "model/apart.h"
using namespace std;

class CGpio
{

public:
    /**
     * @brief The CTimeDispatch class   Inner class to manager timer dispatch.
     */
    class CTimeDispatch
    {
    public:
        CTimeDispatch();
        CTimeDispatch(APart* part);
        CTimeDispatch(APart* part, uint32_t waitTime);
        ~CTimeDispatch() {}

        bool ExpiresTimer();
        APart* GetParts() const { return this->mPart; }
        void UpdateBaseTime();

    public:
        void SetWaitTime(uint32_t waitTime) { this->mWaitTime = waitTime; }
        uint32_t GetWaitTime() { return this->mWaitTime; }

    protected:
        APart* mPart;
        QTime mBaseTime;
        uint32_t mWaitTime; //unit : millisec
    };

    /**
     * @brief The CSpiMode class    Inner class to manage SPI mode.
     */
    class CSpiMode {
    public:
        /*
         * @brief   Enumlator of SPI channel, main or auxiality.
         */
        typedef enum _SPI_CHANNEL {
            SPI_CHANNEL_MAIN = 0u,
            SPI_CHANNEL_AUX,
            SPI_CHANNEL_MAX
        } SPI_CHANNEL;
        /*
         * @brief   Enumlator of SPI mode, from mode 0 to 3.
         */
        typedef enum _SPI_MODE {
            SPI_MODE_0 = 0u,
            SPI_MODE_1,
            SPI_MODE_2,
            SPI_MODE_3,
            SPI_MODE_MAX,
        } SPI_MODE;
        /*
         * @brief   Enumlator of SPI active mode, active when CEx (Chip sElect) signal
         *          is low or high.
         */
        typedef enum _SPI_ACTIVE_MODE {
            SPI_ACTIVE_MODE_LOW = 0u,
            SPI_ACTIVE_MODE_HIGH,
            SPI_ACTIVE_MODE_MAX,
        } SPI_ACTIVE_MODE;
        /*
         * @brief   Enumlator of SPI clock.
         *          By this enumlator, the clock speed can be set a all value in theory.
         *          but to enable to communicate with other device via SPI, the value is
         *          restricted.
         */
        typedef enum _SPI_CLOCK {
            SPI_CLOCK_125K = 125 * 1000,
            SPI_CLOCK_250K = 250 * 1000,
            SPI_CLOCK_500K = 500 * 1000,
            SPI_CLOCK_1M = 1 * 1000 * 1000,
            SPI_CLOCK_10M = 10 * 1000 * 1000,
        } SPI_CLOCK;
        /*
         * @brief   Enumlator of CE, Chip sElection.
         */
        typedef enum _SPI_CE {
            SPI_CE_0 = 0u,
            SPI_CE_1,
            SPI_CE_2,
            SPI_CE_MAX,
        } SPI_CE;
    public:
        CSpiMode();
        CSpiMode(SPI_CHANNEL spiChannel,
                 SPI_MODE spiMode,
                 SPI_ACTIVE_MODE spiActiveModeCe0,
                 SPI_ACTIVE_MODE spiActiveModeCe1,
                 SPI_CLOCK spiClock);
        CSpiMode(SPI_CHANNEL spiChannel,
                 SPI_MODE spiMode,
                 SPI_ACTIVE_MODE spiActiveModeCe0,
                 SPI_ACTIVE_MODE spiActiveModeCe1,
                 SPI_ACTIVE_MODE spiActiveModeCe2,
                 SPI_CLOCK spiClock);
        ~CSpiMode() {}

    public:
        SPI_CHANNEL getSpiChannel() { return this->mSpiChannel; }
        SPI_MODE getSpiMode() { return this->mSpiMode; }
        SPI_ACTIVE_MODE getSpiActiveMode0() { return this->mSpiActiveModeCe0; }
        SPI_ACTIVE_MODE getSpiActiveMode1() { return this->mSpiActiveModeCe1; }
        SPI_ACTIVE_MODE getSpiActiveMode2() { return this->mSpiActiveModeCe2; }
        SPI_CLOCK getSpiClock() { return  this->mSpiClock; }

    protected:
        SPI_CHANNEL mSpiChannel;
        SPI_MODE mSpiMode;
        SPI_ACTIVE_MODE mSpiActiveModeCe0;
        SPI_ACTIVE_MODE mSpiActiveModeCe1;
        SPI_ACTIVE_MODE mSpiActiveModeCe2;
        SPI_CLOCK mSpiClock;
    };

public:
    enum GPIO_PIN_DIRECTION {
        GPIO_PIN_DIRECTION_INPUT = 0,
        GPIO_PIN_DIRECTION_OUTPUT,
        GPIO_PIN_DIRECTION_MAX
    };

    enum GPIO_PIN_LEVEL {
        GPIO_PIN_LEVEL_LOW = 0,
        GPIO_PIN_LEVEL_HIGH,
        GPIO_PIN_LEVEL_MAX,
    };

protected:
    CGpio();
    ~CGpio();

public:
    static void Initialize();
    static void Finalize();
    static CGpio* GetInstance();
    static void Interrupt(int pin, int level, uint32_t tick);
    static void ChatteringTimeDispatch();
    static void PeriodicTimerDispatch();

    void SetMode(uint pin, GPIO_PIN_DIRECTION mode);
    void SetIsr(uint pin, uint edge, APart* part);
    int SetSPI(const CSpiMode* spiMode);
    void SetTimeIsr(APart* part);
    void RemoveTimeIsr(APart* part);
    void IntoCriticalSection() { this->mInCritical = true; }
    void ExitCriticalSection() { this->mInCritical = false; }
    void IntoCriticalSection(uint pin);
    void ExitCriticalSection(uint pin);
    bool IsCriticalSection(uint pin);
    void StartChatteringTimer(APart* part);
    int SpiRead(uint8_t ce, uint8_t *data, uint dataSize);
    int SpiWrite(uint8_t ce, uint8_t *data, uint dataSize);
    int SpiRead(uint8_t ce, APart* part);
    int SpiWrite(uint8_t ce, APart* part);
    int GpioWrite(uint8_t pin, uint8_t level);
    int GpioRead(uint8_t pin, uint8_t* level);

    bool GetInCritical() const { return this->mInCritical; }
    uint8_t GetInterruptPin() const { return this->mInterruptPin; }
    void SetInterruptPin(uint Pin) { this->mInterruptPin = static_cast<uint8_t>(Pin); }
    map<uint, APart*>* GetPinMap() { return this->mPinMap; }
    vector<CTimeDispatch*>* GetTimeDispatch() { return this->mTimeDispatchList; }
    vector<CTimeDispatch*>* GetWaitChattering() { return this->mWaitChatteringList; }
    vector<CTimeDispatch*>* GetPeriodicTime() { return this->mPeriodicTimeList; }

protected:
    void CriticalSection(uint pin, bool isIn);
    int SetupCEx(int pinNo, CSpiMode::SPI_ACTIVE_MODE activeMode);
    int Ce2Pin(uint8_t ce);

protected:
    static CGpio* mInstance;

    int mSpiHandle;
    uint32_t mSpiFlags;

    bool mInCritical;
    uint8_t mInterruptPin;
    map<uint, APart*>* mPinMap;
    map<uint, bool>* mCriticalSectionMap;
    vector<CTimeDispatch*>* mTimeDispatchList;
    vector<CTimeDispatch*>* mWaitChatteringList;
    vector<CTimeDispatch*>* mPeriodicTimeList;
};


#endif // CGPIO_H
