#pragma once

#include <utils/Types.hpp>

#include <string>
#include <vector>

namespace subHandler {

struct File
{
    std::string name;
    std::string path;
    std::string extension;
    std::vector<std::string> content;
    utils::SubType type;
};

}
