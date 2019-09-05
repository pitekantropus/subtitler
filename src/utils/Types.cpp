#include <utils/Types.hpp>

namespace utils {

std::string TimeSrt::toString() const
{
    std::ostringstream result;
    result << std::setfill('0') << std::setw(2) << h << ":"
           << std::setfill('0') << std::setw(2) << m << ":"
           << std::setfill('0') << std::setw(2) << s << ","
           << std::setfill('0') << std::setw(3) << f;
    return result.str();
}

void TimeSrt::addSeconds(double seconds)
{
    double _seconds = _h * 3600 + _m * 60 + _s + (double)_f / 1000;
    _seconds += seconds;

    uint32_t secondsInt = _seconds;

    _f = (_seconds - secondsInt) * 1000;
    _s = (secondsInt % 60) * factor;
    _m = ((secondsInt % 3600) / 60) * factor;
    _h = (secondsInt / 3600) * factor;
}

}
