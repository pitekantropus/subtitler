#include <subHandler/microDvd/MicroDvdHandler.hpp>

#include <regex>

namespace subHandler { namespace microDvd {

MicroDvdHandler::MicroDvdHandler(std::vector<std::string> &content, double FPS)
    : _content(content)
    , _FPS(FPS)
{}

void MicroDvdHandler::moveSubtitles(double seconds)
{
    const int diff = static_cast<int>(seconds * _FPS);
    std::regex re("\\{(\\d+)\\}\\{(\\d+)\\}");
    std::smatch match;
    uint32_t begin = 0;
    uint32_t end = 0;

    for (auto &line : _content)
    {
        if(std::regex_search(line, match, re))
        {
            begin = stoul(match.str(1)) + diff < 0 ? 0 : stoul(match.str(1)) + diff;
            end = stoul(match.str(2)) + diff < 0 ? 0 : stoul(match.str(2)) + diff;
            std::string result = "{" + std::to_string(begin) + "}{" + std::to_string(end) + "}";
            line = std::regex_replace(line, re, result);
        }
    }
}

void MicroDvdHandler::scaleSubtitles(double baseTime, double scale)
{
    std::regex re("\\{(\\d+)\\}\\{(\\d+)\\}");
    std::smatch match;
    double begin, end;
    double base = baseTime * _FPS;
    double diff = 0;

    for (auto &line : _content)
    {
        if(std::regex_search(line, match, re))
        {
            begin = stoul(match.str(1));
            end = stoul(match.str(2));
            diff = (begin - base) * (scale - 1);
            begin += diff;
            diff = (end - base) * (scale - 1);
            end += diff;
            std::string result = "{" + std::to_string(static_cast<uint32_t>(begin)) + "}{" +
                                       std::to_string(static_cast<uint32_t>(end)) + "}";
            line = std::regex_replace(line, re, result);
        }
    }
}

}}
