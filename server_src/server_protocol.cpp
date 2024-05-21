#include "server_protocol.h"

#include <iostream>

#define SUCCESS 0
#define SHUTCODE 2

// El primer mensaje enviado al cliente debe indicarle qué escenarios
// hay disponibles así como las partidas que ya están creadas y están
// disponibles para que el usuario pueda unirse
#define INIT_MSG_SIZE 2
#define MSG_SIZE 0

#define SEND_STILL 0x01
#define SEND_MOV_LEFT 0x02
#define SEND_MOV_RIGHT 0x03
#define SEND_RUN_LEFT 0x04
#define SEND_RUN_RIGHT 0x05
#define SEND_JUMP 0x06
#define SEND_SHOOT 0x07
#define SEND_SPECIAL_MOVE 0x08
#define SEND_INTOXICATED 0x09
#define SEND_DAMAGE 0x0A
#define SEND_DYING 0x0B
#define SEND_DEAD 0x0C
#define SEND_REVIVE 0x0D

// Esta función no es necesaria si INIT_MSG_SIZE = MSG_SIZE
std::vector<uint8_t> ServerProtocol::recv_init_msg(bool &was_closed) {
    std::vector<uint8_t> data;
    uint8_t byte;
    for (int i = 0; i < INIT_MSG_SIZE; i++) {
        sk.recvall(&byte, sizeof(byte), &was_closed);
        data.push_back(byte);
    }
    return data;
}

std::vector<uint8_t> ServerProtocol::recv_msg(bool &was_closed) {
    std::vector<uint8_t> data;
    uint8_t byte;
    for (int i = 0; i < MSG_SIZE; i++) {
        sk.recvall(&byte, sizeof(byte), &was_closed);
        data.push_back(byte);
    }
    return data;
}

void ServerProtocol::send_msg(std::vector<uint8_t> msg, bool &was_closed) {
    int size = msg.size();
    for (int i = 0; i < size; i++) {
        uint8_t byte = msg[i];
        sk.sendall(&byte, sizeof(byte), &was_closed);
    }
}

int ServerProtocol::disconnect() {
    sk.shutdown(SHUTCODE);
    sk.close();
    return SUCCESS;
}
