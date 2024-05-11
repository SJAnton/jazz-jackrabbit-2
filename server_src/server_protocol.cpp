#include "server_protocol.h"

#include <iostream>

#define SUCCESS 0
#define SHUTCODE 2

// El primer mensaje enviado al cliente debe indicarle qué escenarios
// hay disponibles así como las partidas que ya están creadas y están
// disponibles para que el usuario pueda unirse
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

uint8_t ServerProtocol::recv_action(bool &was_closed) {

}

void ServerProtocol::send_msg(uint8_t &enemies_current, uint8_t &enemies_last, bool &was_closed) {
    
}

int ServerProtocol::disconnect() {
    sk.shutdown(SHUTCODE);
    sk.close();
    return SUCCESS;
}
