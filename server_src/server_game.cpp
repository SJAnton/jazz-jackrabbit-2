#include "server_game.h"

#define MSG_SIZE 5

#define STILL 0x11
#define MOV_LEFT 0x12
#define MOVE_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15
#define JUMP 0x16
#define SHOOT 0x17
#define SPECIAL_MOVE 0x18

std::vector<uint8_t> Game::get_actions(Queue<uint8_t> &q) {
    std::vector<uint8_t> data;
    for (int i = 0; i < MSG_SIZE; i++) {
        data.push_back(q.pop());
    }
    return data;
}

void Game::execute_actions(std::vector<uint8_t> &actions) {

}

void Game::move_character(uint8_t &byte, Character &character) {
    if (byte == JUMP) {
        character.jump();
    } else {
        character.move_x_pos(byte);
    }
}

void Game::attack(uint8_t &byte, Character &character) {
    if (byte == SHOOT) {
        character.attack();
    }
}
