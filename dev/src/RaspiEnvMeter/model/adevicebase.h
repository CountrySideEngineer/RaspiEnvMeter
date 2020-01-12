#ifndef ADEVICEBASE_H
#define ADEVICEBASE_H
#include "model/apart.h"
#include "model/cgpio.h"
#include "lib/include/pigpio/pigpio.h"

class ADeviceBase : public APart
{
public:
    ADeviceBase();

    virtual void SetupPin(const uint8_t pin, const int mode);

    virtual uint8_t* GetBuffer() { return data_buffer_; }
    virtual uint32_t GetBufferSize() { return data_buffer_size_; }
    virtual void ShowBuffer();

protected:
    virtual void InitBuffer();

protected:

    uint8_t*    data_buffer_;
    uint32_t     data_buffer_size_;
    int decimal_part_;
    int integer_part_;
};

#endif // ADEVICEBASE_H
