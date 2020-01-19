#include "cmpl115a1device.h"
#include "util/util.h"
#include "model/gpio_pin_layout.h"

const uint8_t CMPL115A1Device::COEFF_READ_COMMAND_SEQUENCE[COEFF_BUFF_INDEX_MAX] = {
    COEFF_READ_COMMAND_A0_MSB,
    COEFF_READ_COMMAND_A0_LSB,
    COEFF_READ_COMMAND_B1_MSB,
    COEFF_READ_COMMAND_B1_LSB,
    COEFF_READ_COMMAND_B2_MSB,
    COEFF_READ_COMMAND_B2_LSB,
    COEFF_READ_COMMAND_C12_MSB,
    COEFF_READ_COMMAND_C12_LSB,
    READ_COMMAND_OUTPUT_DATA,
};
const uint8_t CMPL115A1Device::DATA_READ_COMMAND_SEQUENCE[DATA_BUFF_INDEX_MAX] = {
    DATA_READ_COMMAND_PRESS_MSB,
    DATA_READ_COMMAND_PRESS_LSB,
    DATA_READ_COMMAND_TEMP_MSB,
    DATA_READ_COMMAND_TEMP_LSB,
    READ_COMMAND_OUTPUT_DATA,
};

const float CMPL115A1Device::LSB_A0 = (1.0 / 8.0);
const float CMPL115A1Device::LSB_B1 = (1.0 / 8192.0);
const float CMPL115A1Device::LSB_B2 = (1.0 / 16384.0);
const float CMPL115A1Device::LSB_C12 = (1.0 / 4194304.0);
const float CMPL115A1Device::LSB_TEMP = 1.0;
const float CMPL115A1Device::LSB_PRESS = 1.0;

/**
 * @brief Default constructor of CMPL115A1Device.
 */
CMPL115A1Device::CMPL115A1Device()
{
    uint32_t buff_size = 0;

    //Avoid warning comparing ENUM.
    uint32_t data_buff_index_max = DATA_BUFF_INDEX_MAX;
    uint32_t coeff_buff_index_max = COEFF_BUFF_INDEX_MAX;

    if (data_buff_index_max < coeff_buff_index_max) {
        buff_size = COEFF_BUFF_INDEX_MAX;
    } else {
        /*
         * @Memo: This section will be never run till the sequence to read sensor value
         *        and coefficient to caclurate value from the value. But this is needed
         *        to make it easier to maintainance the code when the sequence is changed.
         */
        buff_size = DATA_BUFF_INDEX_MAX;
    }
    this->data_buffer_size_ = buff_size;
    this->data_buffer_ = new uint8_t[buff_size];
    this->InitBuffer();
    this->Initialize();
}

/**
 * @brief Destructor of CMPL115A1Device.
 */
CMPL115A1Device::~CMPL115A1Device()
{
    Util::SAFE_RELEASE_DATA_ARRAY(&(this->data_buffer_));
}

/**
 * @brief Start sequence to read data or coefficient from the device by setting CE(Chip sElection) pin
 *        to low to activate SPI communication.
 */
void CMPL115A1Device::StartSequence()
{
    CGpio* instance = CGpio::GetInstance();
    instance->GpioWrite(SPI_0_CE0_N, PI_LOW);
    instance->GpioSleep(0, 0, 3 * 1000);
}

/**
 * @brief Stop sequence to read value from sensor.
 */
void CMPL115A1Device::StopSequence()
{
    CGpio* instance = CGpio::GetInstance();
    instance->GpioWrite(SPI_0_CE0_N, PI_HIGH);
}

/**
 * @brief Sequence to send command to read and receive response and store it into the buffer.
 * @param send_data Command data to send.
 * @param recv_data Pointer to buffer to store the receive data.
 * @attention   In this sequence, the size of data sent and received is 1 byte.
 */
void CMPL115A1Device::SendAndRecvCommand(const uint8_t send_data, uint8_t* recv_data)
{
    auto instance = CGpio::GetInstance();

    instance->SpiWrite(const_cast<uint8_t*>((&send_data)), 1);
    instance->SpiRead(recv_data, 1);

    printf("Snd = 0x%02x Rcv = 0x%02x\r\n", send_data, *recv_data);
}

/**
 * @brief Send command code to start reading sensor value.
 */
void CMPL115A1Device::SendStartReadingComand()
{
    uint8_t temp_buffer = 0;

    this->StartSequence();
    this->SendAndRecvCommand(DATA_READ_COMMAND_START_READ, &temp_buffer);
    this->StopSequence();
}

/**
 * @brief Run sequence to read sensor value.
 */
void CMPL115A1Device::ReadSensorData()
{
    this->InitBuffer();

    this->StartSequence();
    for (int index = 0; index < DATA_BUFF_INDEX_MAX; index++) {
        this->SendAndRecvCommand(CMPL115A1Device::DATA_READ_COMMAND_SEQUENCE[index], &(this->data_buffer_[index]));
    }
    this->StopSequence();

    this->ShowBuffer();
}

/**
 * @brief Run sequence to read values used to calcurate pressure.
 */
void CMPL115A1Device::ReadCoefficientData()
{
    this->InitBuffer();

    this->StartSequence();
    for (int index = 0; index < COEFF_BUFF_INDEX_MAX; index++) {
        this->SendAndRecvCommand(COEFF_READ_COMMAND_SEQUENCE[index], &(this->data_buffer_[index]));
    }
    this->StopSequence();
}

/**
 * @brief Calcurate coefficient used to calcurate pressure.
 */
void CMPL115A1Device::CalcCoeff()
{
    this->coefficient_a0_ = Util::Buff2Float(
                this->data_buffer_,
                COEFF_BUFF_INDEX_A0_MSB, COEFF_BUFF_INDEX_A0_LSB, LSB_A0);
    this->coefficient_b1_ = Util::Buff2Float(
                this->data_buffer_,
                COEFF_BUFF_INDEX_B1_MSB, COEFF_BUFF_INDEX_B1_LSB, LSB_B1);
    this->coefficient_b2_ = Util::Buff2Float(
                this->data_buffer_,
                COEFF_BUFF_INDEX_B2_MSB, COEFF_BUFF_INDEX_B2_LSB, LSB_B2);
    this->coefficient_c12_ = Util::Buff2Float(
                this->data_buffer_,
                COEFF_BUFF_INDEX_C12_MSB, COEFF_BUFF_INDEX_C12_LSB, LSB_C12);

    printf("coefficient_a0_= %.3f\r\n", (double)this->coefficient_a0_);
    printf("coefficient_b1_= %.3f\r\n", (double)this->coefficient_b1_);
    printf("coefficient_b2_= %.3f\r\n", (double)this->coefficient_b2_);
    printf("coefficient_c12_= %.3f\r\n", (double)this->coefficient_c12_);

}

/**
 * @brief Calcurate pressure from coefficient and value stored in buffer.
 */
void CMPL115A1Device::CalcPress()
{
    uint16_t raw_data_tadc = (((uint16_t)this->data_buffer_[DATA_BUFF_INDEX_TEMP_MSB]) << 8) +
            this->data_buffer_[DATA_BUFF_INDEX_TEMP_LSB];
    raw_data_tadc >>= 6;
    float tadc = (float)((int16_t)raw_data_tadc);

    uint16_t raw_data_padc = (((uint16_t)this->data_buffer_[DATA_BUFF_INDEX_PRESS_MSB]) << 8) +
            this->data_buffer_[DATA_BUFF_INDEX_PRESS_LSB];
    raw_data_padc >>= 6;
    float padc = (float)((int16_t)raw_data_padc);

    float press_prep = this->coefficient_a0_
            + (this->coefficient_b1_ + this->coefficient_c12_ * tadc) * padc
            + coefficient_b2_ * tadc;
    this->press_ = press_prep * ((115.0 - 50.0) / 1023.0) + 50;
}

/**
 * @brief Run sequence to read and update coefficient.
 */
void CMPL115A1Device::UpdateCoeff()
{
    this->ReadCoefficientData();
    this->CalcCoeff();
}

/**
 * @brief Update pressure value.
 */
void CMPL115A1Device::Update(int32_t /* State */)
{
    printf("void CMPL115A1Device::Update(int32_t) called\r\n");

    this->Update();
}

/**
 * @brief Update pressure value.
 */
void CMPL115A1Device::Update(void)
{
    printf("void CMPL115A1Device::Update(void) called\r\n");

    this->SendStartReadingComand();
    this->ReadSensorData();

    this->CalcPress();
}
