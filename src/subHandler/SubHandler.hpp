#pragma once

#include <subHandler/File.hpp>

namespace subHandler {

class SubHandler
{
public:
    SubHandler(const std::string &path);

    void saveFile() const;
    void saveFile(const std::string &path) const;
    void moveSubtitles(double seconds, double FPS);
    void scaleSubtitles(const std::string &baseScalePoint, const std::string &scalePoint,
                        double secondsToScale, double FPS);
    void convertTo(utils::SubType type);

private:
    std::ifstream openFile(const std::string &path) const;
    void loadFileContent(std::ifstream &file);
    void loadFileData(const std::string &path);
    void loadSubtitlesType();

    File _file;
};

}
