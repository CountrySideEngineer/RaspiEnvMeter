#ifndef CDHT11DEVICE_H
#define CDHT11DEVICE_H

#include <QObject>
#include "adevicebase.h"

class CDHT11Device : public ADeviceBase
{
public:
    enum {
        DATA_RESULT_OK = 0,
        DATA_RESULT_PULLED_UP_TIMEOUT,
        DATA_RESULT_PULLED_DOWN_TIMEOUT,
        DATA_RESULT_SENSOR_PULL_UP_LOW_TIMEOUT,
        DATA_RESULT_SENSOR_PULL_UP_HIGH_TIMEOUT,
        DATA_RESULT_SENSOR_READ_DATA_TIMEOUT,
        DATA_RESULT_SENSOR_READ_DATA_INVALID,
        DATA_RESULT_SENSOR_NO_UPDATA
    };
    
public:
    CDHT11Device();
    virtual ~CDHT11Device() override;

    virtual void Update(int32_t /* State */) override;
    virtual void Update() override;

protected:
    virtual int Read();
    virtual int ReadSequence();
    virtual bool IsScanIntervalPassed();
    virtual void UpdateInterval();
    virtual unsigned int WaitForPulse(const unsigned int level, const unsigned int time);
    virtual bool ValidateCheckSum();
    template<typename T> T MilliToMicro(T milli_sec);

protected:
    enum {
        DATA_BUFF_INDEX_RH_HIGH = 0,
        DATA_BUFF_INDEX_RH_LOW,
        DATA_BUFF_INDEX_T_HIGH,
        DATA_BUFF_INDEX_T_LOW,
        DATA_BUFF_INDEX_CHECK_SUM,
        DATA_BUFF_INDEX_MAX
    };

protected:
    static const unsigned int WAIT_TIME_START_SIGNAL_LOW;     //Wait time the signal is low to start.
    static const unsigned int WAIT_TIME_START_SIGNAL_HIGH;    //Wait time the signal is high to start.
    static const unsigned int SENSOR_READY_TO_OUTPUT_SIGNAL;
    static const unsigned int WAIT_TIME_TO_CHANGE_LOW_BIT;
    static const unsigned int WAIT_TIME_TO_CHANGE_HIGH_BIT;
    static const unsigned int WAIT_SIGNAL_TIME_OUT;
    static const uint32_t SENSOR_READ_INTERVAL;
    static const unsigned int DATA_BUFF_DATA_PART_SIZE;

protected:
    uint32_t current_time_;

};

template<typename T>
inline T CDHT11Device::MilliToMicro(T milli_sec)
{
    return milli_sec * 1000;
}


#endif // CDHT11DEVICE_H
