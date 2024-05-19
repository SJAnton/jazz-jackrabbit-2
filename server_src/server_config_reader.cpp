#include "server_config_reader.h"

std::vector<uint8_t> ServerConfigReader::read(std::string &obj_name) {
    std::vector<uint8_t> data;

    for (YAML::iterator it = node.begin(); it != node.end(); it++) {
        YAML::Node key = it->first;
        YAML::Node value = it->second;
        if (key.as<std::string>() != obj_name) {
            continue;
        }
        for (YAML::iterator val_it = value.begin(); val_it != value.end(); val_it++) {
            YAML::Node map_val = val_it->second;
            data.push_back(map_val.as<uint8_t>());
        }
        break;
    }
    return data;
}
