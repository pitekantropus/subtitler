#include <../interface/SubHandler.hpp>
#include <subHandler/srt/SrtHandler.hpp>
#include <subHandler/microDvd/MicroDvdHandler.hpp>
#include <utils/Types.hpp>
#include <utils/Functions.hpp>

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>

namespace subHandler {

SubHandler::SubHandler(const std::string &path)
{
    auto file = openFile(path);
    loadFileContent(file);
    loadFileData(path);
    loadSubtitlesType();
}

std::ifstream SubHandler::openFile(const std::string &path) const
{
    std::ifstream file(path);
    if(!file)
    {
        throw std::string("Couldn't open file.");
    }
    return file;
}

void SubHandler::loadFileContent(std::ifstream &file)
{
    std::string line;
    while(std::getline(file, line))
    {
        _file.content.push_back(line);
    }
    if(_file.content.empty())
    {
        throw std::string("File is empty.");
    }
}

void SubHandler::loadFileData(const std::string &path)
{
    size_t startPos = path.find_last_of("/") + 1;
    size_t dotPos = path.find_last_of(".");
    _file.name = path.substr(startPos, dotPos - startPos);
    _file.extension = path.substr(dotPos + 1);
    _file.path = path.substr(0, startPos);
}

void SubHandler::loadSubtitlesType()
{
    switch(_file.content.front()[0])
    {
        case '1':
            _file.type = utils::SubType::SRT;
            break;
        case '{':
            _file.type = utils::SubType::MICRO_DVD;
            break;
        default:
            throw std::string("Unsupported subtitles format.");
    }
}

void SubHandler::saveFile() const
{
    std::string destinationPath = _file.path + _file.name + "." + _file.extension;
    std::string backupPath = _file.path + _file.name + "_old" + "." + _file.extension;
    if(std::rename(destinationPath.c_str(), backupPath.c_str()))
    {
        throw std::string("Error during renaming old file.");
    }

    saveFile(destinationPath);
}

void SubHandler::saveFile(const std::string &fileName) const
{
    std::string destinationPath;
    if(fileName[0] == '/')
    {
        destinationPath = fileName;
    }
    else
    {
        destinationPath = _file.path + fileName;
    }

    std::ofstream file(destinationPath);
    if(!file)
    {
        throw std::string("Couldn't create file.");
    }

    for(const auto &line : _file.content)
    {
        file << line << std::endl;
    }
}

void SubHandler::moveSubtitles(double seconds, double FPS)
{
    if(seconds == 0)
        return;
    if(_file.type == utils::SubType::SRT)
    {
        srt::SrtHandler handler(_file.content);
        handler.moveSubtitles(seconds);
    }
    else if(_file.type == utils::SubType::MICRO_DVD)
    {
        microDvd::MicroDvdHandler handler(_file.content, FPS);
        handler.moveSubtitles(seconds);
    }
    else
    {
        throw std::string("Unsupported format for moving");
    }
}

void SubHandler::scaleSubtitles(const std::string &baseScalePoint, const std::string &scalePoint,
                                double secondsToScale, double FPS)
{
    double baseTime = utils::getSecondsFromString(baseScalePoint);
    double scaleTime = utils::getSecondsFromString(scalePoint);
    double scale = (scaleTime + secondsToScale - baseTime) / (scaleTime - baseTime);

    if(_file.type == utils::SubType::SRT)
    {
        srt::SrtHandler handler(_file.content);
        handler.scaleSubtitles(baseTime, scale);
    }
    else if(_file.type == utils::SubType::MICRO_DVD)
    {
        microDvd::MicroDvdHandler handler(_file.content, FPS);
        handler.scaleSubtitles(baseTime, scale);
    }
    else
    {
        throw std::string("Unsupported format for moving");
    }
}

}
