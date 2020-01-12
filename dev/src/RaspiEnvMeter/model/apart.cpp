#include <iostream>
#include <exception>
#include <stdexcept>
#include "apart.h"
using namespace std;

/**
 * @brief APart::APart  Default constructor
 */
APart::APart()
    : mState(0)
    , mInputPin(0)
    , mChatteringTime(0)
    , mPeriodTime(0)
    , mIsFailure(false)
    , mFailureCode(0x0000)
    , mPinDirection(PART_PIN_DIRECTION_NONE)
{}

/**
 * @brief APart::APart  Constructor with argumetn to initialize GPIO pin number, that of direction,
 *                      input, output, or both, and chattering time to handle chattering.
 * @param Pin           Pin No.
 * @param PinDirection  GPIO pin access direction, input, output, or both.
 * @param ChatteringTime    Time to wait until chattering finish.
 */
APart::APart(uint8_t Pin, PART_PIN_DIRECTION PinDirection, uint32_t ChatteringTime, uint32_t PeriodTime)
    : mState(0)
    , mOptionPin(0)
    , mChatteringTime(ChatteringTime)
    , mPeriodTime(PeriodTime)
    , mIsFailure(false)
    , mFailureCode(0x0000)
    , mPinDirection(PinDirection)
{
    if (PART_PIN_DIRECTION_INPUT & PinDirection) {
        this->mInputPin = Pin;
    }
    if (PART_PIN_DIRECTION_OUTPUT & PinDirection) {
        this->mOutputPin = Pin;
    }

    this->mPinDirection = PinDirection;
}

APart::APart(uint8_t InputPin, uint8_t OutputPin, uint32_t ChatterginTime, uint32_t PeriodicTime)
    : mInputPin(InputPin)
    , mOutputPin(OutputPin)
    , mChatteringTime(ChatterginTime)
    , mPeriodTime(PeriodicTime)
{
    int direction = static_cast<int>(PART_PIN_DIRECTION_INPUT) | static_cast<int>(PART_PIN_DIRECTION_OUTPUT);
    this->mPinDirection = static_cast<PART_PIN_DIRECTION>(direction);
}

/**
 * @brief APart::~APart Destructor.
 */
APart::~APart() {}

/**
 * @brief InterruptCallback Callback function called when interrupt has been
 *                          detectec. This function is called immediately if
 *                          member varibable mChatteringTime is zero, otherwise
 *                          called after mChatteringTime passed.
 * @param state Pin level, 0 mean LOW, othervalue is HIGH.
 */
void APart::InterruptCallback(int /* state */) {}


/**
 * @brief APart::TimerCallback  Callback function called periodically. The period is
 *                              set by member variable mPeriodTime. If the value is
 *                              zero, this fuction is never called.
 * @param state Pin level, 0 mean LOW, othervalue is HIGH.
 */
void APart::TimerCallback(int /* state */) {}

/**
 * @brief APart::ToString
 * @return
 */
string APart::ToString()
{
    return to_string(this->mState);

}

/**
 * @brief APart::GetInputPin    Returns input pin No.
 * @return Input pin No.
 * @exception   Throws logic_error if the configuration of pin direction contains "INPUT".
 */
uint8_t APart::GetInputPin()
{
    uint8_t pin;

    if (PART_PIN_DIRECTION_INPUT & this->mPinDirection) {
        pin = this->mInputPin;
    } else {
        throw logic_error("Pin mode is not input");
    }
    return pin;
}

/**
 * @brief APart::SetInputPin    Set the argument value as input pin.
 * @param Pin   Pin No. to set.
 * @exception   Throws logic_error if the configuration of pin direction contains "INPUT".
 */
void APart::SetInputPin(uint8_t Pin)
{
    if (PART_PIN_DIRECTION_INPUT & this->mPinDirection) {
        this->mInputPin = Pin;
    } else {
        throw logic_error("Pin mode is not input");
    }
}

/**
 * @brief APart::GetOutputPin   Retunrs output pin No.
 * @return  Output pin No.
 * @exception   Throws logic_error exception if the configuration of pin direction contains "OUTPUT".
 */
uint8_t APart::GetOutputPin()
{
    uint8_t pin;

    if (PART_PIN_DIRECTION_OUTPUT & this->mPinDirection) {
        pin = this->mOutputPin;
    } else {
        throw logic_error("Pin mode is not output");
    }
    return pin;
}

/**
 * @brief APart::SetOutputPin   Set output pin No.
 * @param Pin   Pin No. to set.
 * @exception   Throws logic_error exception if the configuration of pin direction contains "OUTPUT".
 */
void APart::SetOutputPin(uint8_t Pin)
{
    if (PART_PIN_DIRECTION_OUTPUT & this->mPinDirection) {
        this->mOutputPin = Pin;
    } else {
        throw logic_error("Pin mode is not output");
    }
}
