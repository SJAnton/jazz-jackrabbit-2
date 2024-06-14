#ifndef EDITOR_MAP_CREATOR_H_
#define EDITOR_MAP_CREATOR_H_

#include <yaml-cpp/yaml.h>

#include "../server_src/objects/server_ammo.h"
#include "../server_src/map/server_game_map.h"

class MapCreator {
    private:

    public:
        MapCreator() {};

        void generate_test_flat_map();

        void generate_test_mountain_map();

        void generate_test_random_map();

        void generate_test_snowy_map();

        void save_to_YAML(ServerGameMap &game_map, std::string &name);
};
#endif
