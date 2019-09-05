#pragma once

#include <utils/Types.hpp>

#include <string>
#include <list>

namespace files {

struct File
{
    std::string name;
    std::string path;
    std::string extension;
    std::list<std::string> content;
    utils::SubType type;
};

}
