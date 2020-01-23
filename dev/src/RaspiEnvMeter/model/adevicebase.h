#ifndef ADEVICEBASE_H
#define ADEVICEBASE_H
#include "model/apart.h"
#include "model/cgpio.h"
#include "lib/include/pigpio/pigpio.h"

class ADeviceBase : public APart
{
public:
    ADeviceBase();
    ADeviceBase(uint8_t pin, uint8_t mode);

    virtual void SetupPin(const uint8_t pin, const int mode);

    virtual uint8_t* GetBuffer() { return data_buffer_; }
    virtual uint32_t GetBufferSize() { return data_buffer_size_; }

    virtual int GetDecimalPart() { return  this->decimal_part_; }
    virtual int GetIntegerPart() { return this->integer_part_; }

    virtual void ShowBuffer();
    virtual float GetFloat() { return 0.0; }


protected:
    virtual void InitializeSpi();
    virtual void InitBuffer();

protected:

    uint8_t*    data_buffer_;
    uint32_t    data_buffer_size_;
    int decimal_part_;
    int integer_part_;
};

#endif // ADEVICEBASE_H
