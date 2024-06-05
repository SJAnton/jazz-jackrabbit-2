#include <fstream>
#include <iostream>

#include "client_dummy_app.h"
#include "client_dummy_protocol.h"

#define ACTION_WALK 0x12
#define LEFT 0x4C
#define RIGHT 0x52

#define MOV_IZQ "IZQ"
#define MOV_DER "DER"
#define EXIT "q"

#define ID_MSG_SIZE 1

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
    ClientApp app(protocol);

    std::string input;
    bool was_closed = false;

    // Elección de partida y personaje
    app.get_games(was_closed);
    std::vector<uint8_t> init_data = app.choose_game_and_character();
    protocol.send_msg(init_data, was_closed);

    // ID del cliente
    uint8_t client_id = protocol.recv_msg(ID_MSG_SIZE, was_closed)[0];
    std::cout << "ID del cliente: " << static_cast<int>(client_id) << std::endl;

    std::cout << "Ingresar movimiento (IZQ, DER, q):" << std::endl;
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
