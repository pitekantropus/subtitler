#include <string>

namespace utils {

template <class T>
T stringToNumber(const std::string &str)
{
    return static_cast<T>(std::stoll(str));
}

std::pair<std::string, std::string> tokenize(const std::string &str, const std::string &token = "=")
{
    size_t pos = str.find(token);
    if(pos == std::string::npos)
    {
        throw std::string("bad parameter");
    }
    std::pair<std::string, std::string> result;
    result.first = str.substr(0, pos);
    result.second = str.substr(pos + token.size());
    return result;
}

}
