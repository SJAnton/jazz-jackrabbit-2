#ifndef SERVER_CONFIG_READER_H_
#define SERVER_CONFIG_READER_H_

#include <iostream>
#include <yaml-cpp/yaml.h>

class ServerConfigReader {
    private:
        YAML::Node node;

    public:
        ServerConfigReader(std::istream &file) {
            node = YAML::Load(file);
        };

        std::map<std::string, std::vector<uint8_t>> read();
};
#endif
