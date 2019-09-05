#pragma once

#include <sstream>
#include <iomanip>

namespace utils {

enum class SubType
{
    SRT = 0,
    MICRO_DVD
};

struct TimeSrt
{
    uint8_t _h;
    uint8_t _m;
    uint8_t _s;
    uint16_t _f;

    std::string toString() const;
    void addSeconds(double seconds);
};

}
