#include "server_config_reader.h"

std::map<std::string, std::vector<uint8_t>> ServerConfigReader::read() {
    std::map<std::string, std::vector<uint8_t>> data;

    for (YAML::iterator it = node.begin(); it != node.end(); it++) {
        std::vector<uint8_t> values;
        
        YAML::Node key = it->first;
        YAML::Node value = it->second;

        for (YAML::iterator val_it = value.begin(); val_it != value.end(); val_it++) {
            YAML::Node map_val = val_it->second;
            values.push_back(map_val.as<uint8_t>());
        }
        data[key.as<std::string>()] = values;
    }
    return data;
}
