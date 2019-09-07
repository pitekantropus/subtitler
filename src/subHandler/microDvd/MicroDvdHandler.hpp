#pragma once

#include <vector>
#include <string>

namespace subHandler { namespace microDvd {

class MicroDvdHandler
{
public:
    MicroDvdHandler(std::vector<std::string> &content, double FPS);
    ~MicroDvdHandler() = default;

    void moveSubtitles(double seconds);
    void scaleSubtitles(double baseTime, double scale);

private:
    std::vector<std::string> &_content;
    double _FPS;
};

}}
