#include <iostream>
#include <assert.h>
#include <list>
#include <vector>
#include <QObject>
#include <QtDebug>
#include "pigpio/pigpio.h"
#include "apart.h"
#include "cgpio.h"


/*
 * Timer macro used in time configuration.
 */
//Timer id.
#define TIMER_ID_CHATTERING_TIMER       (0)
#define TIMER_ID_PERIODIC_TIMER         (1)

//Time period in millisecond unit.
#define TIMER_PERIOD_CHATTERING_TIMER   (20)    //20 msec
#define TIMER_PERIOD_PERIODIC_TIMER     (10)    //10 msec

using namespace std;

CGpio* CGpio::mInstance = nullptr;


/**
 * @brief CGpio::CGpio  Constructor of CGpio class.
 *                      In this method, member variable mIsCritical and mInterruptPin
 *                      are initialized.
 */
CGpio::CGpio()
    : mInCritical(false)
    , mInterruptPin(0xFF)
{
    this->mPinMap = new map<uint, APart*>();
    this->mCriticalSectionMap = new map<uint, bool>();
    this->mWaitChatteringList = new vector<CTimeDispatch*>();
    this->mTimeDispatchList = new vector<CTimeDispatch*>();
    this->mPeriodicTimeList = new vector<CTimeDispatch*>();

    this->mSpiHandle = -1;
    this->mSpiFlags = 0;
}
#define DELETE_MEMBER_POINTER(mPtr)     \
    {                                   \
        delete mPtr;                    \
        mPtr = nullptr;                 \
    }

#define DELETE_MEMBER_MAP(mVectorPtr)               \
{                                                   \
    auto VectorIt = mVectorPtr->begin();            \
    while (VectorIt != mVectorPtr->end()) {         \
        auto item = (*VectorIt).second;             \
        VectorIt++;                                 \
        delete item;                                \
    }                                               \
    DELETE_MEMBER_POINTER(mVectorPtr);              \
}

#define DELETE_MEMBER_VECTOR(mMapPtr)           \
    {                                           \
        auto MapIt = mMapPtr->begin();          \
        while (MapIt != mMapPtr->end()) {       \
            MapIt = mMapPtr->erase(MapIt);      \
        }                                       \
        DELETE_MEMBER_POINTER(mMapPtr);         \
    }

/**
 * @brief CGpio::~CGpio Destructor.
 */
CGpio::~CGpio()
{
    DELETE_MEMBER_POINTER(this->mPinMap);
    DELETE_MEMBER_POINTER(this->mCriticalSectionMap);
    DELETE_MEMBER_VECTOR(this->mWaitChatteringList);
    DELETE_MEMBER_VECTOR(this->mTimeDispatchList);
    DELETE_MEMBER_VECTOR(this->mPeriodicTimeList);
}

/**
 * @brief CGpio::Initialize Initialize GPIO library, and create instance of
 *                          CGpio class if the library initializing finished
 *                          successfully.
 */
void CGpio::Initialize()
{
    if (gpioInitialise() < 0) {
        //GPIO library initialize failed.
        cout << "gpioInitialise() failed" << endl;
    } else {
        if (nullptr == CGpio::mInstance) {
            CGpio::mInstance = new CGpio();

            gpioSetTimerFunc(TIMER_ID_PERIODIC_TIMER,
                             TIMER_PERIOD_PERIODIC_TIMER,
                             CGpio::PeriodicTimerDispatch);
            gpioSetTimerFunc(TIMER_ID_CHATTERING_TIMER,
                             TIMER_PERIOD_CHATTERING_TIMER,
                             CGpio::ChatteringTimeDispatch);
        }
    }
}

/**
 * @brief CGpio::Finalize   Finalize, in other word terminte, the GPIO library
 *                          and delete CGpio instance.
 */
void CGpio::Finalize()
{
    gpioSetTimerFunc(TIMER_ID_PERIODIC_TIMER, TIMER_PERIOD_PERIODIC_TIMER, nullptr);
    gpioSetTimerFunc(TIMER_ID_CHATTERING_TIMER, TIMER_PERIOD_CHATTERING_TIMER, nullptr);
    gpioTerminate();

    if (nullptr != CGpio::mInstance) {
        delete CGpio::mInstance;
        CGpio::mInstance = nullptr;
    }
}

/**
 * @brief CGpio::GetIntance Returns instande of pointer to CGpio instance.
 * @return
 */
CGpio* CGpio::GetInstance()
{
    if (nullptr == CGpio::mInstance) {
        CGpio::Initialize();
    }
    return CGpio::mInstance;
}

/**
 * @brief CGpio::SetMode    Set mode of Pin, INPUT or OUTPUT.
 * @param pin   Pin number of GPIO pin.
 * @param mode  Pin mode, INPUT or OUTPUT.
 */
void CGpio::SetMode(uint pin, GPIO_PIN_DIRECTION mode)
{
    uint directoin = 0;
    if (GPIO_PIN_DIRECTION_INPUT == mode) {
        directoin = PI_INPUT;
    } else if (GPIO_PIN_DIRECTION_OUTPUT == mode) {
        directoin = PI_OUTPUT;
    } else {
        directoin = 0xFF;
    }
    /*
     * Variable "direction" is not checked because, if it is invalid,
     * the library, "gpioSetMode", returns invalid result, maybe PI_BAD_MODE.
     */

    /**
     * @ToDo    Throw exception if the GPIO library returned
     *          not OK value.
     */
    int result = gpioSetMode(pin, directoin);
    if (PI_BAD_GPIO == result) {
        cout << "gpioSetMode() failed because of PI_BAD_GPIO" << endl;
    } else if (PI_BAD_MODE == result) {
        cout << "gpioSetMode() failed because of PI_BAD_MODE" << endl;
    }
}

/**
 * @brief CGpio::Interrupt  Interrupt callback function.
 * @param pin   Pin of GPIO.
 */
void CGpio::Interrupt(int pin, int /* level */, uint32_t /* tick */)
{
    CGpio* instance = CGpio::GetInstance();
    uint interruptPin = static_cast<uint>(pin);
    if (0 == instance->GetPinMap()->count(interruptPin)) {
        return;
    }

    if (false == instance->IsCriticalSection(interruptPin)) {
        instance->IntoCriticalSection(interruptPin);
        APart* part = instance->GetPinMap()->at(interruptPin);
        if (0 == part->GetChatteringTime()) {
            int state = gpioRead(part->GetPin());
            part->InterruptCallback(state);
            instance->ExitCriticalSection(interruptPin);
        } else {
            instance->StartChatteringTimer(part);
        }
    }
}

/**
 * @brief CGpio::StartChatteringTimer   Start chattering timer.
 * @param part
 */
void CGpio::StartChatteringTimer(APart* part)
{
    assert(nullptr != part);

    this->mWaitChatteringList->push_back(new CTimeDispatch(part));
}

/**
 * @brief CGpio::ChatteringTimeDispatch Callback function called when a time
 *                                      set to wait for chattering is expired.
 */
void CGpio::ChatteringTimeDispatch()
{
    CGpio* instance = CGpio::GetInstance();
    vector<CTimeDispatch*>* waitChatteringList = instance->GetWaitChattering();
    auto it = waitChatteringList->begin();
    while (it != waitChatteringList->end()) {
        CTimeDispatch* timeDispatch = *it;
        if (timeDispatch->ExpiresTimer()) {
            APart* part = timeDispatch->GetParts();
            uint8_t gpioPin = part->GetPin();
            int level = gpioRead(gpioPin);
            part->InterruptCallback(level);

            instance->ExitCriticalSection(gpioPin);

            it = instance->GetWaitChattering()->erase(it);
            /*
             * There is no need to delete parts, CParts object, because
             * the memory is released when the erase method is called at
             * the same time.
             */
        } else {
            it++;
        }
    }
}

/**
 * @brief CGpio::PeriodicTimerDispatch  Callback function called when timer dispatched.
 *                                      Attention, this functino is supposed called in
 *                                      periodically.
 */
void CGpio::PeriodicTimerDispatch()
{
    CGpio* instance = CGpio::GetInstance();
    vector<CTimeDispatch*>* periodicTImeList = instance->GetPeriodicTime();
    auto it = periodicTImeList->begin();
    while (it != periodicTImeList->end()) {
        CTimeDispatch* timeDispatch = *it;
        if (timeDispatch->ExpiresTimer()) {
            APart* part = timeDispatch->GetParts();
            uint8_t pin = part->GetPin();
            int level = gpioRead(pin);
            part->TimerCallback(level);

            timeDispatch->UpdateBaseTime();
        }
        it++;
    }
}

/**
 * @brief CGpio::SetIsr Setup GPIO pin interrupt mode.
 * @param pin   Pin number Of GPIO to setup.
 * @param edge  Edge the callback function will be called,
 *              raise up or falling down.
 * @param part  Pointer to CParts object to call.
 */
void CGpio::SetIsr(uint pin, uint edge, APart* part)
{
    assert(nullptr != this->mPinMap);

    if (nullptr == part) {
        /*
         * @ToDo:
         *      Throw exception if the variable "part" is nullprt.
         */
        return;
    }

    /*
     * @ToDo    Throw exception if the GPIO library returned
     *          not OK value.
     */
    int result = gpioSetISRFunc(pin, edge, 0, CGpio::Interrupt);
    if (PI_BAD_GPIO == result) {
        cout << "gpioSetISRFunc() failed because PI_BAD_GPIO" << endl;
    } else if (PI_BAD_EDGE == result) {
        cout << "gpioSetISRFunc() failed because PI_BAD_EDGE" << endl;
    } else if (PI_BAD_ISR_INIT == result) {
        cout << "gpioSetISRFunc() failed because PI_BAD_ISR_INIT" << endl;
    } else {
        if (0 != this->mPinMap->count(pin)) {
            cout << pin << " has already registered as ISR pin." << endl;
        } else {
            (*(this->mPinMap))[pin] = part;
            (*(this->mCriticalSectionMap))[pin] = false;
        }
    }
}

/**
 * @brief CGpio::SetTimeIsr Setup callback function called when a time is dispatched.
 * @param part  Part data to be called when the time is dispatched.
 */
void CGpio::SetTimeIsr(APart *part)
{
    assert(nullptr != this->mPeriodicTimeList);
    assert(nullptr != part);

    /*
     *  The periodic timer has been started when the instance of CGpio class, singleton,
     *  was initialized.
     *  So, the function to regist callback, and so on, does not need to be called
     *  in this method.
     */
    this->mPeriodicTimeList->push_back(new CTimeDispatch(part, part->GetPeriodTime()));
}

/**
 * @brief CGpio::RemoveTimeIsr  Remove timer dispatcher from periodic timer list.
 * @param targetPart    Pointer to Apart class to be removed from the list.
 */
void CGpio::RemoveTimeIsr(APart *targetPart)
{
    auto it = this->mPeriodicTimeList->begin();
    while (it != this->mPeriodicTimeList->end()) {
        CTimeDispatch* timeDispatch = *it;
        APart* part = timeDispatch->GetParts();
        if (part == targetPart) {
            this->mPeriodicTimeList->erase(it);
            /*
             * There is no need to delete parts, CParts object, because
             * the memory is released when the erase method is called at
             * the same time.
             */
        } else {
            it++;
        }
    }
}

/**
 * @brief CGpio::IntoCriticalSection    Set a pin into critical section.
 * @param pin   GPIO pin number.
 */
void CGpio::IntoCriticalSection(uint pin) { this->CriticalSection(pin, true); }

/**
 * @brief CGpio::ExitCriticalSection    Exit a pin from critical section.
 * @param pin   GPIO pin number.
 */
void CGpio::ExitCriticalSection(uint pin) { this->CriticalSection(pin, false); }

/**
 * @brief CGpio::CriticalSection    Main method to manage critical section.
 * @param pin   GPIO pin number.
 * @param isIn  Critical section state, true means "being in critical section",
 *              otherwise not in critical section.
 */
void CGpio::CriticalSection(uint pin, bool isIn)
{
    assert(nullptr != this->mCriticalSectionMap);

    try {
        (*(this->mCriticalSectionMap))[pin] = isIn;
    } catch (out_of_range& ex) {
        cout << ex.what() << endl;
    }
}

/**
 * @brief CGpio::IsCriticalSection  Returns critical section state of GPIO pin
 * @param pin   GPIO pin number.
 * @return Returns TRUE if in critical section, otherwise false.
 */
bool CGpio::IsCriticalSection(uint pin)
{
    assert(nullptr != this->mCriticalSectionMap);
    try {
        return (*(this->mCriticalSectionMap))[pin];
    } catch (out_of_range& ex) {
        cout << ex.what() << endl;

        return false;
    }
}

#define SPI_CE0_ACTIVE_MODE(active_mode)        ((active_mode) << 2)
#define SPI_CE1_ACTIVE_MODE(active_mode)        ((active_mode) << 3)
#define SPI_CE2_ACTIVE_MODE(active_mode)        ((active_mode) << 4)
#define SPI_CHANNEL_MAIN_OR_AUX(spi_channel)    ((spi_channel) << 8)
#define GPIO_7              (7)
#define GPIO_8              (8)
#define GPIO_16             (16)
#define GPIO_17             (17)
#define GPIO_18             (18)
#define SPI0_MAIN_CE0       (GPIO_8)
#define SPI0_MAIN_CE1       (GPIO_7)
#define SPI1_AUX_CE0        (GPIO_18)
#define SPI1_AUX_CE1        (GPIO_17)
#define SPI1_AUX_CE2        (GPIO_16)

/**
 * @brief CGpio::SetSPI Setup SPI communicaton mode.
 * @param spiMode   CspiMode object contains the mode information.
 */
int CGpio::SetSPI(CSpiMode const *spiParam)
{
    CSpiMode* _spiParam = const_cast<CSpiMode*>(spiParam);
    if (this->mSpiHandle < 0) {
        //To avoid the SPI port to being opened duplicated.
        uint32_t _spiFlags =
                SPI_CHANNEL_MAIN_OR_AUX(static_cast<uint32_t>(_spiParam->getSpiChannel()))
                | SPI_CE0_ACTIVE_MODE(static_cast<uint32_t>(_spiParam->getSpiActiveMode0()))
                | SPI_CE1_ACTIVE_MODE(static_cast<uint32_t>(_spiParam->getSpiActiveMode1()))
                | SPI_CE2_ACTIVE_MODE(static_cast<uint32_t>(_spiParam->getSpiActiveMode2()))
                | static_cast<uint32_t>(_spiParam->getSpiMode());
        int _spiHandle = spiOpen(0,
                                 _spiParam->getSpiClock(),
                                 static_cast<unsigned int>(_spiFlags));
        if (_spiHandle < 0) {
            this->mSpiHandle = -1;

            cout << "spiOpen() failed." << endl;

            return (-1);
        } else {
            this->mSpiHandle = _spiHandle;
            this->mSpiFlags = _spiFlags;
        }
    }

    int setupResult0 = 0;
    int setupResult1 = 0;
    int setupResult2 = 0;
    if (CSpiMode::SPI_CHANNEL_MAIN == _spiParam->getSpiChannel()) {
        setupResult0 = SetupCEx(SPI0_MAIN_CE0, _spiParam->getSpiActiveMode0());
        setupResult1 = SetupCEx(SPI0_MAIN_CE1, _spiParam->getSpiActiveMode1());
    } else {
        setupResult0 = SetupCEx(SPI1_AUX_CE0, _spiParam->getSpiActiveMode0());
        setupResult1 = SetupCEx(SPI1_AUX_CE1, _spiParam->getSpiActiveMode1());
        setupResult2 = SetupCEx(SPI1_AUX_CE2, _spiParam->getSpiActiveMode2());
    }

    if ((setupResult0 < 0) || (setupResult1 < 0) || (setupResult2 < 0)) {
        return (-1);
    } else {
        return 0;
    }
}

/**
 * @brief CGpio::SetupCEx   Setup SPI signal pin, set to the pin mode as OUTPUT
 *                          and the CE pin lenel.
 * @param pinNo         The pin No. to be used to select slave device.
 * @param activeMode    The level to activate a slave device.
 */
int CGpio::SetupCEx(int pinNo, CSpiMode::SPI_ACTIVE_MODE activeMode)
{
    int result = 0;
    result = gpioSetMode(static_cast<unsigned int>(pinNo), PI_OUTPUT);
    if (result < 0) {
        cout << "The gpioSetMode() failed." << endl;

        return result;
    }

    uint deactivePinLevel = 0;
    if (CSpiMode::SPI_ACTIVE_MODE::SPI_ACTIVE_MODE_LOW == activeMode) {
        deactivePinLevel = PI_HIGH;
    } else {
        deactivePinLevel = PI_LOW;
    }
    result = gpioWrite(static_cast<uint>(pinNo), deactivePinLevel);
    if (result < 0) {
        cout << "The gpioWrite() failed." << endl;
    }

    return result;
}

/**
 * @brief CGpio::SpiRead    Receive data from slave device via SPI communication.
 * @param ce                Chip sElect No.
 * @param data              Pointer to buffer to store data sent from slave device.
 * @param dataSize          The size of buffer to sotre data.
 * @return Size of receive data in byte.
 */
int CGpio::SpiRead(uint8_t ce, uint8_t *data, uint dataSize)
{
    int cePin = this->Ce2Pin(ce);
    if (cePin < 0) {
        cout << "INVALID CE" << endl;

        return (-1);
    }

    uint32_t activeLevelFlag = (this->mSpiFlags & (1 << (ce + 5)));
    uint activeLevel = 0;
    if (0 == activeLevelFlag) {
        activeLevel = 0;
    } else {
        activeLevel = 1;
    }

    uint deactiveLevel = (0 == activeLevel) ? 1 : 0;

    gpioWrite(static_cast<unsigned int>(cePin), activeLevel);
    int sentDataSize = spiRead(static_cast<unsigned int>(this->mSpiHandle),
                               reinterpret_cast<char *>(data),
                               dataSize);
    gpioWrite(static_cast<unsigned int>(cePin), deactiveLevel);

    return  sentDataSize;
}

/**
 * @brief CGpio::SpiRead    Receive data from slave device via SPI communication.
 * @param ce                Chip sElect No.
 * @param part              Pointer to part to read data.
 * @return Size of receive data in byte.
 */
int CGpio::SpiRead(uint8_t ce, APart* part) {
    return this->SpiRead(ce, part->GetBuffer(), part->GetBufferSize());
}

/**
 * @brief CGpio::SpiWrite   Send data to slave device via SPI communication.
 * @param ce                Chip sElect No.
 * @param data              Pointer to buffer which stores the datas to send by SPI communication.
 * @param dataSize          The data size to send.
 * @return  Size of sent data.
 */
int CGpio::SpiWrite(uint8_t ce, uint8_t *data, uint dataSize)
{
    int cePin = this->Ce2Pin(ce);
    if (cePin < 0) {
        return (-1);
    }

    uint activeLevel = (this->mSpiFlags & (1 << (ce + 5)));
    uint deactiveLevel = (0 == activeLevel) ? 1 : 0;

    gpioWrite(static_cast<unsigned int>(cePin), activeLevel);
    int recvDataSize = spiWrite(static_cast<unsigned int>(this->mSpiHandle),
                                reinterpret_cast<char*>(data),
                                dataSize);
    gpioWrite(static_cast<unsigned int>(cePin), deactiveLevel);

    return recvDataSize;
}

/**
 * @brief CGpio::SpiWrite   Send data to slave device via SPI communication.
 * @param ce                Chip sElect No.
 * @param part              Pointer to buffer which stores the datas to send by SPI communication.
 * @return  Size of sent data.
 */
int CGpio::SpiWrite(uint8_t ce, APart* part) {
    return this->SpiWrite(ce, part->GetBuffer(), part->GetBufferSize());
}

/**
 * @brief CGpio::Ce2Pin     Convert CE No.(from 0 to 1 in Main, 0 to 2 in AUX) into GPIO pin No.
 * @param ce                CE No. to be converted.
 * @return  GPIO pin No.. If an error occurred, the value is -1.
 */
int CGpio::Ce2Pin(uint8_t ce) {
    int cePin = 0;
    if (this->mSpiHandle < 0) {
        //A case that the spi has not been setup.
        cout << "SPI has not been configured." << endl;
        return (-1);
    }

    int spiChannel = (this->mSpiFlags & (1 << 8));
    if (0 == spiChannel) {
        switch (ce) {
        case 0:
            cePin = SPI0_MAIN_CE0;
            break;

        case 1:
            cePin = SPI0_MAIN_CE1;
            break;

        default:
            cePin = (-1);
            break;
        }
    } else {
        switch (ce) {
        case 0:
            cePin = SPI1_AUX_CE0;
            break;

        case 1:
            cePin = SPI1_AUX_CE1;
            break;

        case 2:
            cePin = SPI1_AUX_CE2;
            break;

        default:
            cePin = (-1);
            break;
        }
    }
    return cePin;
}

/**
 * @brief CGpio::GpioWrite  Sets the GPIO level into on or off.
 * @param pin       The gpio number to change the level.
 * @param level     Pin level, on or off.
 * @return  Returns the result of level change.
 */
int CGpio::GpioWrite(uint8_t pin, uint8_t level)
{
    assert((1 == level) || (0 == level));

    return gpioWrite(pin, level);
}

/**
 * @brief CGpio::GpioRead   Reads the GPIO level, on or off.
 * @param pin   The gpio pin number to read the level.
 * @param level Pointer to set the read level.
 * @return  Returs -1 if the access failed, otherwise 0.
 */
int CGpio::GpioRead(uint8_t pin, uint8_t *level)
{
    assert(NULL != level);

    int readLevel = gpioRead(pin);
    int readResult = -1;
    if (PI_BAD_GPIO == readLevel) {
        readResult = -1;
    } else {
        readResult = 0;
        *level = static_cast<uint8_t>(readLevel);
    }

    return readResult;
}

/**
 * @brief CGpio::CTimeDispatch::CTimeDispatch   Constructor of CTimeDispatch, inner class,
 *                                              default constructor.
 */
CGpio::CTimeDispatch::CTimeDispatch()
    : mPart(nullptr)
    , mWaitTime(0)
{
    this->mBaseTime = QTime::currentTime();
}

/**
 * @brief CGpio::CTimeDispatch::CTimeDispatch   Destructor of CTimeDispatch class.
 * @param parts
 */
CGpio::CTimeDispatch::CTimeDispatch(APart* part)
    : mPart(part)
    , mWaitTime(part->GetChatteringTime())
{
    this->mBaseTime = QTime::currentTime();
}

/**
 * @brief CGpio::CTimeDispatch::CTimeDispatch   Destructor of CTimeDispatch class.
 * @param parts
 */
CGpio::CTimeDispatch::CTimeDispatch(APart* part, uint32_t waitTime)
    : mPart(part)
    , mWaitTime(waitTime)
{
    this->mBaseTime = QTime::currentTime();
}

/**
 * @brief CGpio::CTimeDispatch::ExpiresTimer    Returns whether the time has been expired or not.
 * @return  Returns true if the time has been expired, otherwise returns false.
 */
bool CGpio::CTimeDispatch::ExpiresTimer()
{
    QTime currentTime = QTime::currentTime();

    /*
     *  The value msecsTo returns will not be negative, but just a reminder, convert the data type
     *  of value from signed into unsigned.
     */
    uint32_t passedTime = static_cast<uint32_t>(abs(currentTime.msecsTo(this->mBaseTime)));
    if (this->mWaitTime <= passedTime) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief CGpio::CTimeDispatch::UpdateBaseTime  Update base time which will be used in
 *                                              calcurating the time is passed.
 */
void CGpio::CTimeDispatch::UpdateBaseTime()
{
    this->mBaseTime = QTime::currentTime();
}

/**
 * @brief CGpio::CSpiMode::CSpiMode Constructor of CSpiMode class without argument.
 */
CGpio::CSpiMode::CSpiMode()
    : CSpiMode(SPI_CHANNEL_MAIN,
           SPI_MODE_0,
           SPI_ACTIVE_MODE_LOW,
           SPI_ACTIVE_MODE_LOW,
           SPI_CLOCK_125K)
{}

/**
 * @brief CGpio::CSpiMode::CSpiMode Constructor of CSpiMode class with argument to
 *                                  initialize parameters
 * @param spiChannel    Channel to be used in SPI communication, MAIN or AUX.
 * @param spiMode       Mode of SPI, mode0 to mode3
 * @param spiActiveModeCe0  Signal level to activate slave 0 device, HIGH or LOW.
 *                          ex. if the value is set to HIGH, the slave 0 is active
 *                              when the CE0 signal is HIGH, otherwise it is active
 *                              when the signal is low.
 * @param spiActiveModeCe1  Signal level to activate slave 1 device, HIGH or LOW.
 * @param spiClock          The clock speed to synchronize slave device.
 */
CGpio::CSpiMode::CSpiMode(
        SPI_CHANNEL spiChannel,
        SPI_MODE spiMode,
        SPI_ACTIVE_MODE spiActiveModeCe0,
        SPI_ACTIVE_MODE spiActiveModeCe1,
        SPI_CLOCK spiClock)
    : CSpiMode(spiChannel,
               spiMode,
               spiActiveModeCe0,
               spiActiveModeCe1,
               SPI_ACTIVE_MODE_LOW,
               spiClock)
{}

/**
 * @brief CGpio::CSpiMode::CSpiMode Constructor of CSpiMode class with argument to
 *                                  initialize parameters.
 * @param spiChannel    Channel to be used in SPI communication, MAIN or AUX.
 * @param spiMode       Mode of SPI, mode0 to mode3.
 * @param spiActiveModeCe0  Signal level to activate slace 0 device, HIGH or LOW.
 *                          ex. if the value is set to HIGH, the slave 0 is active
 *                              when the CE0 signal is HIGH, otherwise it is active
 *                              when the signal is low.
 * @param spiActiveModeCe1  Signal level to activate slace 1 device, HIGH or LOW.
 * @param spiActiveModeCe2  Signal level to activate slace 2 device, HIGH or LOW.
 *                          This parameter is avaialable only when the spi channel is
 *                          AUX (spiChannel is SPI_CHANNEL_AUX).
 * @param spiClock          The clock speed to synchronize slave device.
 */
CGpio::CSpiMode::CSpiMode(
        SPI_CHANNEL spiChannel,
        SPI_MODE spiMode,
        SPI_ACTIVE_MODE spiActiveModeCe0,
        SPI_ACTIVE_MODE spiActiveModeCe1,
        SPI_ACTIVE_MODE spiActiveModeCe2,
        SPI_CLOCK spiClock)
    : mSpiChannel(spiChannel)
    , mSpiMode(spiMode)
    , mSpiActiveModeCe0(spiActiveModeCe0)
    , mSpiActiveModeCe1(spiActiveModeCe1)
    , mSpiActiveModeCe2(spiActiveModeCe2)
    , mSpiClock(spiClock)
{}
