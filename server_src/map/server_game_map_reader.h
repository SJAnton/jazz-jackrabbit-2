#ifndef SERVER_GAME_MAP_READER_H_
#define SERVER_GAME_MAP_READER_H_

#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

class ServerGameMapReader {
    private:
        YAML::Node node;

    public:
        ServerGameMapReader(std::istream &file) {
            node = YAML::Load(file);
        };

        std::vector<std::string> get_levels();
};
#endif
