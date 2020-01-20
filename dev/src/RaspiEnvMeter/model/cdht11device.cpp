#include <math.h>
#include "cdht11device.h"
#include "model/cgpio.h"

const unsigned int CDHT11Device::WAIT_TIME_START_SIGNAL_LOW = 20;    //20 milli sec
const unsigned int CDHT11Device::WAIT_TIME_START_SIGNAL_HIGH = 80;   //80 milli sec
const unsigned int CDHT11Device::SENSOR_READY_TO_OUTPUT_SIGNAL = 80;
const unsigned int CDHT11Device::WAIT_TIME_TO_CHANGE_LOW_BIT = 50;
const unsigned int CDHT11Device::WAIT_TIME_TO_CHANGE_HIGH_BIT = 70;
const unsigned int CDHT11Device::WAIT_SIGNAL_TIME_OUT = (unsigned int)(-1);
const uint32_t CDHT11Device::SENSOR_READ_INTERVAL = 2000000;    //2 second.
const unsigned int CDHT11Device::DATA_BUFF_DATA_PART_SIZE = 4;


/**
 * @brief Constructor of CDHT11Device.
 */
CDHT11Device::CDHT11Device()
    : current_time_(0)
{
    this->data_buffer_size_ = DATA_BUFF_INDEX_MAX;
    this->data_buffer_ = new uint8_t[this->data_buffer_size_];
    this->InitBuffer();
    this->Initialize();
}

/**
 * @brief Desutructor of CDHT11Device.
 */
CDHT11Device::~CDHT11Device() {}

/**
 * @brief Update value by reading and converting sensor value.
 */
void CDHT11Device::Update(int32_t /* State */)
{
    this->Update();
}

/**
 * @brief Update value by reading and converting sensor value.
 */
void CDHT11Device::Update()
{
    this->Read();
}

/**
 * @brief Read sensor value.
 * @return  Result of reading the value.
 *          Returns 0 if the reading finished successfully, otherwise returns not 0 value.
 */
int CDHT11Device::Read()
{
    if (this->IsScanIntervalPassed()) {
        this->ReadSequence();
    }
    this->UpdateInterval();

    return 0;
}

/**
 * @brief   Run sequence to read data from senor.
 * @return  Returns 0 if successfully, otherwise returns none 0 value.
 */
int CDHT11Device::ReadSequence()
{
    uint32_t recv_raw_data_buff[80] = { 0 };
    CGpio* instance = CGpio::GetInstance();

    //Step1:Sending start signal.
    instance->SetMode(this->GetPin(), CGpio::GPIO_PIN_DIRECTION_OUTPUT);
    instance->SetPullUpDownMode(this->GetPin(), CGpio::GPIO_PULL_UP_DOWN_OFF);
    instance->GpioWrite(this->GetPin(), CGpio::GPIO_PIN_LEVEL_LOW);
    instance->GpioSleep(0, 0, WAIT_TIME_START_SIGNAL_LOW);

    //Step2:Waiting for response signal by settin GPIO pin pulled up.
    instance->SetMode(this->GetPin(), CGpio::GPIO_PIN_DIRECTION_INPUT);
    instance->SetPullUpDownMode(this->GetPin(), CGpio::GPIO_PULL_UP_DOWN_UP);
    this->WaitForPulse(CGpio::GPIO_PIN_LEVEL_LOW, this->MilliToMicro(WAIT_TIME_START_SIGNAL_HIGH));
    if (WAIT_SIGNAL_TIME_OUT == this->WaitForPulse(
                CGpio::GPIO_PIN_LEVEL_HIGH,
                WAIT_TIME_START_SIGNAL_HIGH))
    {
        return DATA_RESULT_PULLED_UP_TIMEOUT;
    }

    /*
     *  Step3:Waiting for response singal sensor send to nptify host that the device
     *  is ready to communicate with.
     */
    if (WAIT_SIGNAL_TIME_OUT == this->WaitForPulse(
                CGpio::GPIO_PIN_LEVEL_LOW,
                SENSOR_READY_TO_OUTPUT_SIGNAL))
    {
        return DATA_RESULT_SENSOR_PULL_UP_LOW_TIMEOUT;
    }
    if (WAIT_SIGNAL_TIME_OUT == this->WaitForPulse(
                CGpio::GPIO_PIN_LEVEL_HIGH,
                SENSOR_READY_TO_OUTPUT_SIGNAL))
    {
        return DATA_RESULT_SENSOR_PULL_UP_HIGH_TIMEOUT;
    }

    //Step4:Read signal from sensor by comparing time the signal low and high.
    for (int index = 0; index < 40; index++) {
        recv_raw_data_buff[index * 2] = this->WaitForPulse(
                    CGpio::GPIO_PIN_LEVEL_LOW,
                    WAIT_TIME_TO_CHANGE_LOW_BIT);
        recv_raw_data_buff[index * 2 + 1] = this->WaitForPulse(
                    CGpio::GPIO_PIN_LEVEL_HIGH,
                    WAIT_TIME_TO_CHANGE_HIGH_BIT);
    }

    //Step5:Convert recv raw data, time the pin level is low and high to bit data.
    this->InitBuffer();
    for (int index = 0; index < 40; index++) {
        uint32_t start_bit_time = recv_raw_data_buff[index * 2];
        uint32_t follow_bit_time = recv_raw_data_buff[index * 2 + 1];
        if ((WAIT_SIGNAL_TIME_OUT == start_bit_time) ||
            (WAIT_SIGNAL_TIME_OUT == follow_bit_time))
        {
            return DATA_RESULT_SENSOR_READ_DATA_TIMEOUT;
        }
        this->data_buffer_[index / 8] <<= 1;
        if (start_bit_time < follow_bit_time) {
            this->data_buffer_[index / 8] |= 1;
        }
    }

    //Step6:Validate receive data by checking sum.
    if (!this->ValidateCheckSum()) {
        return DATA_RESULT_SENSOR_READ_DATA_INVALID;
    } else {
        return DATA_RESULT_OK;
    }
}

/**
 * @brief Wait while the pin level is kept.
 * @param level Pin level, low or high, to wait while.
 * @param time  Time to wait for in micro second unit.
 * @return  Actual passed time.
 */
uint32_t CDHT11Device::WaitForPulse(const unsigned int level, const unsigned int time)
{
    uint8_t read_level = 0;

    CGpio* instance = CGpio::GetInstance();
    instance->GpioRead(this->GetPin(), &read_level);

    uint32_t passed_time = 0;
    while (read_level == level) {
        if (time < passed_time) {
            return WAIT_SIGNAL_TIME_OUT;
        }
        instance->GpioRead(this->GetPin(), &read_level);
        instance->GpioDelay(1);

    }
    return passed_time;
}

/**
 * @brief Check whether the interval is passed.
 * @return  Returns true if the time to be needed to wait to ready to get next sensor data passed,
 *          otherwise returns false.
 */
bool CDHT11Device::IsScanIntervalPassed()
{
    bool is_passed = false;
    CGpio* instance = CGpio::GetInstance();
    uint32_t current_time = instance->GetCurrentTime();
    if (SENSOR_READ_INTERVAL < current_time - this->current_time_) {
        is_passed  = true;
    } else {
        is_passed = false;

    }
    return is_passed;
}

/**
 * @brief Update current time to be used to check snesor read interval.
 */
void CDHT11Device::UpdateInterval()
{
    CGpio* instance = CGpio::GetInstance();
    this->current_time_ = instance->GetCurrentTime();
}

bool CDHT11Device::ValidateCheckSum()
{
    uint16_t check_sum = 0;
    for (int buff_index = 0; buff_index < DATA_BUFF_DATA_PART_SIZE; buff_index++) {
        check_sum += this->data_buffer_[buff_index];
    }

    if ((uint8_t)check_sum == this->data_buffer_[DATA_BUFF_INDEX_CHECK_SUM]) {
        return true;
    } else {
        return false;
    }
}

void CDHT11Device::UpdateValues()
{
    this->temperature_ = (int32_t)((uint16_t)(this->data_buffer_[DATA_BUFF_INDEX_T_HIGH] & 0x07) << 8) +
                        this->data_buffer_[DATA_BUFF_INDEX_T_LOW];
    if (0 != (this->data_buffer_[DATA_BUFF_INDEX_T_HIGH] & 0x80)) {
        /*
         * If the MSB, sign bit is 1, ti mean that the temperature is minus.
         * To set the value minus, multiple temppeature_ by minus one.
         */
        this->temperature_ *= (-1);
    } else {
        /*
         * Temperature is over 0.
         * So nothing to do.
         */
    }
}

/**
 * @brief Returns the integer part of temperature.
 * @return  Integer part of temperature.
 */
int32_t CDHT11Device::GetTemperature_Integer()
{
    return (int32_t)(this->temperature_ / 256);
}

/**
 * @brief Returns the decimal part of temperature.
 * @return  Decimal part of temperature.
 */
uint32_t CDHT11Device::GetTemperature_Decimal()
{
    return (uint32_t)(abs(this->temperature_ % 256));
}

