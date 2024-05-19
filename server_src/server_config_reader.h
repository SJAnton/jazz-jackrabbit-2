#ifndef SERVER_CONFIG_READER_H_
#define SERVER_CONFIG_READER_H_

// sudo apt-get install libyaml-cpp-dev
#include <iostream>
#include <yaml-cpp/yaml.h>

class ServerConfigReader {
    private:
        YAML::Node node;

    public:
        ServerConfigReader(std::istream &file) {
            node = YAML::Load(file);
        };

        std::vector<uint8_t> read(std::string &obj_name);
};
#endif
