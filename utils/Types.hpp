#pragma once

namespace utils {

enum class SubType
{
    SRT = 0,
    MICRO_DVD
};

struct TimeSrt
{
    uint8_t h;
    uint8_t m;
    uint8_t s;
    uint16_t f;
}

}
