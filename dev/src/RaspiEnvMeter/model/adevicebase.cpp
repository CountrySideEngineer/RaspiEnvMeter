#include "adevicebase.h"
#include "model/gpio_pin_layout.h"

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
    printf("\r\n");
}

/**
 * @brief Initialize and setup SPI configuration.
 */
void ADeviceBase::InitializeSpi()
{
    CGpio* instance = CGpio::GetInstance();
    instance->SetMode(SPI_0_CE0_N, CGpio::GPIO_PIN_DIRECTION::GPIO_PIN_DIRECTION_OUTPUT);
    instance->SetMode(SPI_0_CE1_N, CGpio::GPIO_PIN_DIRECTION::GPIO_PIN_DIRECTION_OUTPUT);

    this->SetOutputPin(SPI_0_CE0_N);
    this->SetOutputPin(SPI_0_CE1_N);

    CGpio::CSpiMode spi_mode(CGpio::CSpiMode::SPI_CHANNEL_MAIN,
                             CGpio::CSpiMode::SPI_MODE_0,
                             CGpio::CSpiMode::SPI_ACTIVE_MODE_LOW,
                             CGpio::CSpiMode::SPI_ACTIVE_MODE_LOW,
                             CGpio::CSpiMode::SPI_CLOCK_4M);
    instance->SetSPI(&spi_mode);
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
