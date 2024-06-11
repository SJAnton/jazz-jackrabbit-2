#include "client_dummy_app.h"

#include <iostream>

void ClientApp::get_games(bool &wc) {
    //uint8_t size = protocol.get_msg_size(wc);
    std::vector<uint8_t> games = protocol.recv_msg(wc);

    if (games.empty()) {
        std::cout << "No hay partidas activas" << std::endl;
        return;
    }
    std::cout << "Partidas disponibles:" << std::endl;
    for (uint8_t game_id : games) {
        std::cout << "ID: " << static_cast<int>(game_id) << std::endl;
    }
}

std::vector<uint8_t> ClientApp::choose_game_and_character() {
    std::vector<uint8_t> init_data;
    std::string input;

    std::cout << "Ingresar ID de la partida (nueva partida = 0):" << std::endl;
    std::getline(std::cin, input);
    uint8_t game_byte = atoi(input.c_str());

    std::cout << "Ingresar personaje (1 = Jazz, 2 = Lori, 3 = Spaz):" << std::endl;
    std::getline(std::cin, input);
    uint8_t character_byte = atoi(input.c_str());

    init_data.push_back(game_byte);
    init_data.push_back(character_byte);
    return init_data;
}
