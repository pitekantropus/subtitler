#include <subHandler/srt/SrtHandler.hpp>
#include <utils/Types.hpp>
#include <utils/Functions.hpp>

#include <regex>

namespace subHandler { namespace srt {

const std::regex RE("(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}) --> (\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})");

SrtHandler::SrtHandler(std::vector<std::string> &content)
    : _content(content)
{}

void SrtHandler::moveSubtitles(double seconds)
{
    utils::TimeSrt begin, end;

    for(size_t i = 1; i < _content.size() - 4; ++i)
    {
        if(parseLineIfPossible(_content[i], begin, end))
        {
            begin.addSeconds(seconds);
            end.addSeconds(seconds);
            _content[i] = begin.toString() + " --> " + end.toString();
        }
    }
}

void SrtHandler::scaleSubtitles(double baseTime, double scale)
{
    utils::TimeSrt begin, end;
    double diff = 0;

    for(size_t i = 1; i < _content.size() - 4; ++i)
    {
        if(parseLineIfPossible(_content[i], begin, end))
        {
            diff = (begin.getSeconds() - baseTime) * (scale - 1);
            begin.addSeconds(diff);
            diff = (begin.getSeconds() - baseTime) * (scale - 1);
            end.addSeconds(diff);
            _content[i] = begin.toString() + " --> " + end.toString();
        }
    }
}

bool SrtHandler::parseLineIfPossible(const std::string &line, utils::TimeSrt &begin,
                                          utils::TimeSrt &end) const
{
    std::smatch match;

    if(std::regex_search(line, match, RE))
    {
        begin = {utils::stringToNumber<uint16_t>(match.str(1)),
                 utils::stringToNumber<uint16_t>(match.str(2)),
                 utils::stringToNumber<uint16_t>(match.str(3)),
                 utils::stringToNumber<uint16_t>(match.str(4))};
        end = {utils::stringToNumber<uint16_t>(match.str(5)),
               utils::stringToNumber<uint16_t>(match.str(6)),
               utils::stringToNumber<uint16_t>(match.str(7)),
               utils::stringToNumber<uint16_t>(match.str(8))};
        return true;
    }
    return false;
}

}}
