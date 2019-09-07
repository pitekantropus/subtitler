#include <utils/Types.hpp>

namespace utils {

std::string TimeSrt::toString() const
{
    std::ostringstream result;
    result << std::setfill('0') << std::setw(2) << _h << ":"
           << std::setfill('0') << std::setw(2) << _m << ":"
           << std::setfill('0') << std::setw(2) << _s << ","
           << std::setfill('0') << std::setw(3) << _f;
    return result.str();
}

void TimeSrt::addSeconds(double seconds)
{
    double _seconds = getSeconds();
    _seconds += seconds;

    uint32_t secondsInt = _seconds;

    _f = (_seconds - secondsInt) * 1000;
    _s = secondsInt % 60;
    _m = (secondsInt % 3600) / 60;
    _h = secondsInt / 3600;
}

double TimeSrt::getSeconds() const
{
    return _h * 3600 + _m * 60 + _s + _f / 1000.0;
}

}
