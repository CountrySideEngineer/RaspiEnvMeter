#include "util.h"

Util::Util() { }

float Util::Buff2Float(const uint8_t *buffer, int msb_index, int lsb_index, float lsb, uint16_t mask)
{
    uint16_t raw_data = (((uint16_t)buffer[msb_index]) << 8) + (uint16_t)buffer[lsb_index];
    raw_data &= mask;
    float converted = (float)((int16_t)raw_data * lsb);

    return  converted;
}
