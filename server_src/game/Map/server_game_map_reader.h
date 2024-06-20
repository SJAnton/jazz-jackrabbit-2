#ifndef SERVER_GAME_MAP_READER_H_
#define SERVER_GAME_MAP_READER_H_

#include <fstream>
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

#include "../objects/server_ammo.h"
#include "../map/server_game_map.h"

class ServerGameMapReader {
    private:
        YAML::Node node;

        std::vector<std::string> get_levels();

    public:
        ServerGameMapReader() {};

        std::map<uint8_t, ServerGameMap> read_levels();
};
#endif
