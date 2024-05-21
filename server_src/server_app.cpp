#include "server_app.h"

#define JAZZ_BYTE 0x00
#define LORI_BYTE 0x01
#define SPAZ_BYTE 0x02

#define JAZZ_CODE "PlayerJazz"
#define LORI_CODE "PlayerLori"
#define SPAZ_CODE "PlayerSpaz"

#define STILL 0x11
#define MOV_LEFT 0x12
#define MOVE_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15
#define JUMP 0x16
#define SHOOT 0x17
#define SPECIAL_MOVE 0x18

Character ServerApp::choose_character(uint8_t &byte,
                        std::map<std::string, std::vector<uint8_t>> &data) {
    Character ch;
    if (byte == JAZZ_BYTE) {
        PlayerJazz player(data[JAZZ_CODE]);
        ch = player;
    } else if (byte == LORI_BYTE) {
        PlayerLori player(data[LORI_CODE]);
        ch = player;
    } else {
        PlayerSpaz player(data[SPAZ_CODE]);
        ch = player;
    }
    return ch;
}

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
