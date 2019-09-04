#pragma once

#include <files/File.hpp>

namespace files {

class SubHandler
{
public:
    SubHandler(const std::string &path);

    void saveFile() const;
    void saveFile(const std::string &path);
    void moveSubtitles(double seconds);
    void scaleSubtitles(double scale);
    void convertTo(utils::SubType type);

private:
    std::ifstream openFile(const std::string &path) const;
    void loadFileContent(std::ifstream &file);
    void loadFileData(const std::string &path);
    void loadSubtitlesType();

    File _file;
};

}
