#include "adevicebase.h"

/**
 * @brief   Default constructor of ADeviceBase class.
 */
ADeviceBase::ADeviceBase()
    : APart ()
    , decimal_part_(0)
    , integer_part_(0)
{}

/**
 * @brief Setup pin and mode.
 * @param pin   GPIO pin number
 * @param mode  GPIO pin direction, the value 1 means input, 2 means output, and other means invalid.
 *              If the value is invlid, no notification will be sent.
 */
void ADeviceBase::SetupPin(const uint8_t pin, const int mode)
{
    APart::SetPin(pin);
    APart::SetPinDirection((PART_PIN_DIRECTION)mode);
}

/**
 * @brief   Print buffer content with a 16 byte each line.
 */
void ADeviceBase::ShowBuffer()
{
    if (nullptr == this->data_buffer_) {
        printf("Data buffer has not been setup.\r\n");
        return;
    }

    for (uint32_t index = 0; index < this->data_buffer_size_;index++) {
        if ((0 != index) && (0 == (index % 16))) {
            printf("\r\n");
        } else {
            printf(" ");
        }
        printf("0x%02x", this->data_buffer_[index]);
    }
}

/**
 * @brief   Initialize data buffer.
 */
void ADeviceBase::InitBuffer()
{
    if (nullptr == this->data_buffer_) {
        printf("Data buffer has not been setup.\r\n");
        return;
    }

    for (uint32_t index = 0; index < this->data_buffer_size_;index++) {
        this->data_buffer_[index] = 0;
    }
}
