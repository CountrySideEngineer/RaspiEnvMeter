#ifndef UTIL_H
#define UTIL_H
#include "lib/include/pigpio/pigpio.h"

class Util
{
public:
    Util();

    template<typename T> static void SAFE_RELEASE_DATA(T** target)
    {
        T* target_ptr = *target;
        if (nullptr != target_ptr) {
            delete *target;
            *target = nullptr;
        }
    }
    template<typename T> static void SAFE_RELEASE_DATA_ARRAY(T** target)
    {
        T* target_ptr = *target;
        if (nullptr != target_ptr) {
            delete [] *target;
            *target = nullptr;
        }
    }

    static float Buff2Float(const uint8_t* buffer, int msb_index, int lsb_index, float lsb, uint16_t mask = 0xFFFF);
    static float kPaTohPa(float kPa) { return kPa * 10; }
    static int float2int(float value) { return static_cast<int>(value); }
};

#endif // UTIL_H
