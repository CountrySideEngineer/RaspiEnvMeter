#ifndef CMPL115A1DEVICE_H
#define CMPL115A1DEVICE_H
#include "adevicebase.h"

class CMPL115A1Device : public ADeviceBase
{
public:
    CMPL115A1Device();
    virtual ~CMPL115A1Device() override;

    virtual void Update(int32_t /* State */) override;
    virtual void Update() override;
    virtual void UpdateCoeff();

    virtual void Initialize() override;

    virtual float GetFloat() override { return this->press_; }

protected:
    virtual void StartSequence();
    virtual void StopSequence();
    virtual void SendAndRecvCommand(const uint8_t send_data, uint8_t* recv_data);

    virtual void SendStartReadingComand();
    virtual void ReadSensorData();
    virtual void ReadCoefficientData();

    virtual int CalcValue() { return 0; }
    virtual void CalcCoeff();
    virtual void CalcPress();

    virtual void ShowCoefficient();

protected:
    enum {
        COEFF_BUFF_INDEX_A0_MSB = 0,
        COEFF_BUFF_INDEX_A0_LSB,
        COEFF_BUFF_INDEX_B1_MSB,
        COEFF_BUFF_INDEX_B1_LSB,
        COEFF_BUFF_INDEX_B2_MSB,
        COEFF_BUFF_INDEX_B2_LSB,
        COEFF_BUFF_INDEX_C12_MSB,
        COEFF_BUFF_INDEX_C12_LSB,
        COEFF_BUFF_INDEX_EXTRA,
        COEFF_BUFF_INDEX_MAX,
    };
    enum {
        DATA_BUFF_INDEX_PRESS_MSB = 0,
        DATA_BUFF_INDEX_PRESS_LSB,
        DATA_BUFF_INDEX_TEMP_MSB,
        DATA_BUFF_INDEX_TEMP_LSB,
        DATA_BUFF_INDEX_EXTRA,
        DATA_BUFF_INDEX_MAX,
    };
    static const uint8_t READ_COMMAND_OUTPUT_DATA = 0x00;
    static const uint8_t DATA_READ_COMMAND_START_READ = 0x24;
    static const uint8_t DATA_READ_COMMAND_PRESS_MSB = 0x80;
    static const uint8_t DATA_READ_COMMAND_PRESS_LSB = 0x82;
    static const uint8_t DATA_READ_COMMAND_TEMP_MSB = 0x84;
    static const uint8_t DATA_READ_COMMAND_TEMP_LSB = 0x86;
    static const uint8_t COEFF_READ_COMMAND_A0_MSB = 0x88;
    static const uint8_t COEFF_READ_COMMAND_A0_LSB = 0x8A;
    static const uint8_t COEFF_READ_COMMAND_B1_MSB = 0x8C;
    static const uint8_t COEFF_READ_COMMAND_B1_LSB = 0x8E;
    static const uint8_t COEFF_READ_COMMAND_B2_MSB = 0x90;
    static const uint8_t COEFF_READ_COMMAND_B2_LSB = 0x92;
    static const uint8_t COEFF_READ_COMMAND_C12_MSB = 0x94;
    static const uint8_t COEFF_READ_COMMAND_C12_LSB = 0x96;

    static const uint8_t COEFF_READ_COMMAND_SEQUENCE[];
    static const uint8_t DATA_READ_COMMAND_SEQUENCE[];

    static const float LSB_A0;
    static const float LSB_B1;
    static const float LSB_B2;
    static const float LSB_C12;
    static const float LSB_PRESS;
    static const float LSB_TEMP;

protected:
    float coefficient_a0_;
    float coefficient_b1_;
    float coefficient_b2_;
    float coefficient_c12_;
    float press_;
};

#endif // CMPL115A1DEVICE_H
