#ifndef SERVER_APP_H_
#define SERVER_APP_H_

#include <map>
#include <vector>

#include "server_client.h"
#include "characters/server_character.h"

class ServerApp {
    private:

    public:
        ServerApp() {};

        void move_character(uint8_t &byte, Character &character);

        void attack(uint8_t &byte, Character &character);
};
#endif
