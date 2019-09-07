#pragma once

#include <vector>
#include <string>

namespace utils {
    class TimeSrt;
}

namespace subHandler { namespace srt {

class SrtHandler
{
public:
    SrtHandler(std::vector<std::string> &content);
    ~SrtHandler() = default;

    void moveSubtitles(double seconds);
    void scaleSubtitles(double baseTime, double scale);

private:
    bool parseLineIfPossible(const std::string &line, utils::TimeSrt &begin,
                             utils::TimeSrt &end) const;

    std::vector<std::string> &_content;
};

}}
