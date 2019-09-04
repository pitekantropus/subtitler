#include <files/SubHandler.hpp>

#include <iostream>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout<<"Invalid parameter number."<<std::endl;
        return 1;
    }

    try
    {
        files::SubHandler handler(argv[1]);
        handler.moveSubtitles(atof(argv[2]));
        handler.saveFile();
    }
    catch (std::string ex)
    {
        std::cout<<"Exception caught: "<<ex<<std::endl;
        return 1;
    }

    return 0;
}