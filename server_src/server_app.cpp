#include "server_app.h"

#define STILL 0x11
#define MOV_LEFT 0x12
#define MOVE_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15
#define JUMP 0x16
#define SHOOT 0x17
#define SPECIAL_MOVE 0x18

void ServerApp::move_character(uint8_t &byte, Character &character) {
    if (byte == JUMP) {
        character.jump();
    } else {
        character.move_x_pos(byte);
    }
}

void ServerApp::attack(uint8_t &byte, Character &character) {
    if (byte == SHOOT) {
        character.attack();
    }
}
