#pragma once

#include <string>

namespace utils {

template <class T>
T stringToNumber(const std::string &str)
{
    return static_cast<T>(std::stoll(str));
}

double getSecondsFromString(const std::string &str);

}
