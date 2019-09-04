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
    bool positive = seconds >= 0;
    seconds = positive ? seconds : seconds * (-1);

    uint16_t f = seconds - static_cast<int>(seconds);
}

}
