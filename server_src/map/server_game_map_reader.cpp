#include "server_game_map_reader.h"

#include <iostream>
#include <filesystem>

#define CURRENT_FOLDER_LENGTH 6 // "/build"
#define LEVELS_FOLDER "/levels" 

// c_cpp_properties.json --> cppStandard: "c++17"
namespace fs = std::filesystem;

std::vector<std::string> ServerGameMapReader::get_levels() {
    std::vector<std::string> levels_path;

    std::string path = fs::current_path();

    path.erase(path.length() - CURRENT_FOLDER_LENGTH);
    path += LEVELS_FOLDER;

    for (auto &dir : std::filesystem::directory_iterator(path)) {
        levels_path.push_back((dir.path()));
    }
    return levels_path;
}
