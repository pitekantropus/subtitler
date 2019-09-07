#include <subHandler/SubHandler.hpp>
#include <utils/Functions.hpp>

#include <iostream>

int main(int argc, char **argv)
{
    std::string filePath;
    std::string destPath;
    double secondsToMove = 0;
    std::string baseScalePoint;
    std::string scalePoint;
    double secondsToScale = 0;
    double FPS = 23.97;

    for(size_t i = 1; i < argc; i++)
    {
        auto item = utils::tokenize(argv[i]);
        if(item.first == "filePath")
        {
            filePath = item.second;
        }
        else if(item.first == "destPath")
        {
            destPath = item.second;
        }
        else if(item.first == "move")
        {
            secondsToMove = std::stod(item.second);
        }
        else if(item.first == "baseScaleTime")
        {
            baseScalePoint = item.second;
        }
        else if(item.first == "scaleTime")
        {
            scalePoint = item.second;
        }
        else if(item.first == "scaleMove")
        {
            secondsToScale = std::stod(item.second);
        }
        else if(item.first == "FPS")
        {
            FPS = std::stod(item.second);
        }
        else
        {
            std::cout<<"Unknown parameter: "<<item.first<<std::endl;
        }
    }

    try
    {
        subHandler::SubHandler handler(filePath);
        handler.moveSubtitles(secondsToMove, FPS);
        if(!scalePoint.empty())
        {
            handler.scaleSubtitles(baseScalePoint, scalePoint, secondsToScale, FPS);
        }
        destPath.empty() ? handler.saveFile() : handler.saveFile(destPath);
    }
    catch (std::string ex)
    {
        std::cout<<"Exception caught: "<<ex<<std::endl;
        return 1;
    }

    return 0;
}