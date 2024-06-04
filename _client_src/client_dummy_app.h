#ifndef CLIENT_DUMMY_APP_H_
#define CLIENT_DUMMY_APP_H_

#include "client_dummy_protocol.h"

class ClientApp {
    private:
        ClientProtocol &protocol;

    public:
        ClientApp(ClientProtocol &protocol) : protocol(protocol) {};

        void get_games(bool &wc);

        std::vector<uint8_t> choose_game_and_character();
};
#endif
