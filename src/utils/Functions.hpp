#pragma once

#include <string>

namespace utils {

template <class T>
T stringToNumber(const std::string &str)
{
    return static_cast<T>(std::stoll(str));
}

std::pair<std::string, std::string> tokenize(const std::string &str, const std::string &token = "=");
double getSecondsFromString(const std::string &str);

}
