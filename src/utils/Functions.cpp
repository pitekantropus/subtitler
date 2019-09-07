#include <utils/Functions.hpp>

#include <regex>

namespace utils {

double getSecondsFromString(const std::string &str)
{
    std::regex hhmmssfff("(\\d{2}):(\\d{2}):(\\d{2})[\\.,](\\d{3})");
    std::regex ssfff("(\\d+)[\\.,](\\d+)");
    std::smatch match;

    if(std::regex_match(str, match, hhmmssfff))
    {
        return stod(match.str(1)) * 3600 + stod(match.str(2)) * 60 +
               stod(match.str(3)) + stod(match.str(4)) / 1000.0;
    }
    else if(std::regex_match(str, match, ssfff))
    {
        return stod(match.str(1)) + stod(match.str(2)) / 1000.0;
    }
    else
    {
        throw std::string("Unrecognized seconds format.");
    }
}

}
