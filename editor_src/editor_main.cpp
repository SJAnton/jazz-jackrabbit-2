#include "editor_map_creator.h"

int main() {
    MapCreator map_creator;

    map_creator.generate_test_flat_map();
    map_creator.generate_test_mountain_map();
    map_creator.generate_test_random_map();
    map_creator.generate_test_snowy_map();

    return 0;
}