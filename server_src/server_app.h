#ifndef SERVER_APP_H_
#define SERVER_APP_H_

#include <map>
#include <vector>

#include "server_client.h"
#include "characters/server_character.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"

class ServerApp {
    private:

    public:
        ServerApp() {};

        Character choose_character(uint8_t &byte,
                    std::map<std::string, std::vector<uint8_t>> &data);

        void move_character(uint8_t &byte, Character &character);

        void attack(uint8_t &byte, Character &character);
};
#endif
