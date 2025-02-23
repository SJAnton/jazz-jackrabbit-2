#ifndef EDITOR_MAP_CREATOR_H_
#define EDITOR_MAP_CREATOR_H_

#include <yaml-cpp/yaml.h>

#include "../server_src/game/Map/game_map.h"

class MapWriter {
    private:
        std::string enemy_type_to_str(const TipoEnemy &type);

        std::string object_type_to_str(const TipoRecolectable &type);

    public:
        MapWriter() {};

        void generate_test_flat_map();

        void generate_test_mountain_map();

        void generate_test_random_map();

        void generate_test_snowy_map();

        void save_to_YAML(GameMap &game_map, std::string &name);
};
#endif
