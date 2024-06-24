#include "server_config_reader.h"

std::map<std::string, std::vector<int>> ServerConfigReader::read() {
    std::map<std::string, std::vector<int>> data;

    for (YAML::iterator it = node.begin(); it != node.end(); it++) {
        std::vector<int> values;
        
        YAML::Node key = it->first;
        YAML::Node value = it->second;

        for (YAML::iterator val_it = value.begin(); val_it != value.end(); val_it++) {
            YAML::Node map_val = val_it->second;
            values.push_back(map_val.as<int>());
        }
        data[key.as<std::string>()] = values;
    }
    return data;
}
