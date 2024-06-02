#include <fstream>
#include <iostream>

#include "client_dummy_protocol.h"

#define GAME_BYTE 0x01

#define JAZZ_BYTE 0x01
#define LORI_BYTE 0x02
#define SPAZ_BYTE 0x03

#define ACTION_WALK 0x12
#define LEFT 0x4C
#define RIGHT 0x52

#define MOV_IZQ "IZQ"
#define MOV_DER "DER"
#define EXIT "q"

#define EXIT_BYTE 0xFF

#define SUCCESS 0
#define ERROR 1

#define HOSTNAME argv[1]
#define SERVICENAME argv[2]

int main(int argc, char* argv[]) {
    if (HOSTNAME == nullptr || SERVICENAME == nullptr) {
        throw std::invalid_argument("No hostname or servicename found");
        return ERROR;
    }
    ClientProtocol protocol(HOSTNAME, SERVICENAME);

    std::string input;
    bool was_closed = false;

    std::vector<uint8_t> init_data = {GAME_BYTE, JAZZ_BYTE};
    protocol.send_msg(init_data, was_closed);
    uint8_t client_id = protocol.get_id(was_closed);

    while (std::getline(std::cin, input)) {
        try {
            if (input == MOV_IZQ) {
                std::vector<uint8_t> actions = {client_id, ACTION_WALK, LEFT};
                protocol.send_msg(actions, was_closed);
            } else if (input == MOV_DER) {
                std::vector<uint8_t> actions = {client_id, ACTION_WALK, RIGHT};
                protocol.send_msg(actions, was_closed);
            } else if (input == EXIT) {
                std::vector<uint8_t> actions = {EXIT_BYTE, EXIT_BYTE, EXIT_BYTE};
                protocol.send_msg(actions, was_closed);
                break;
            }

        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    was_closed = true;
    protocol.disconnect();
    return SUCCESS;
}
