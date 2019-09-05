#include <files/SubHandler.hpp>
#include <utils/Types.hpp>
#include <utils/Functions.hpp>

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>

namespace files {

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
    std::string originalPath = _file.path + _file.name + "." + _file.extension;
    std::string backupPath = _file.path + _file.name + "_old" + "." + _file.extension;
    if(std::rename(originalPath.c_str(), backupPath.c_str()))
    {
        throw std::string("Error during renaming old file.");
    }

    std::ofstream file(originalPath);
    if(!file)
    {
        throw std::string("Couldn't open file.");
    }

    for(const auto &line : _file.content)
    {
        file << line << std::endl;
    }
}

void SubHandler::moveSubtitles(double seconds)
{
    const double FPS = 23.97;
    const int diff = static_cast<int>(seconds * FPS);
    std::regex re("\\{(\\d+)\\}\\{(\\d+)\\}");
    std::smatch match;
    uint32_t begin = 0;
    uint32_t end = 0;

    if(_file.type == utils::SubType::MICRO_DVD)
    {
        for(auto &line : _file.content)
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
    else if(_file.type == utils::SubType::SRT)
    {
        size_t i = 0;
        std::regex re("(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}) --> (\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})");
        std::smatch match;
        utils::TimeSrt begin, end;

        for(auto &line : _file.content)
        {
            if(i % 4 == 1 && std::regex_search(line, match, re))
            {
                begin = {utils::stringToNumber<uint8_t>(match.str(1)),
                         utils::stringToNumber<uint8_t>(match.str(2)),
                         utils::stringToNumber<uint8_t>(match.str(3)),
                         utils::stringToNumber<uint16_t>(match.str(4))};
                end = {utils::stringToNumber<uint8_t>(match.str(5)),
                       utils::stringToNumber<uint8_t>(match.str(6)),
                       utils::stringToNumber<uint8_t>(match.str(7)),
                       utils::stringToNumber<uint16_t>(match.str(8))};
            }
        }
    }
    else
    {
        throw std::string("Unsupported format for moving");
    }
}

}
