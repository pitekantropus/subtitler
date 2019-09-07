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
    uint16_t _h;
    uint16_t _m;
    uint16_t _s;
    uint16_t _f;

    std::string toString() const;
    void addSeconds(double seconds);
};

}
