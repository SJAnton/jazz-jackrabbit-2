#include "server_protocol.h"

#include <iostream>

#define SUCCESS 0
#define SHUTCODE 2

#define INIT_MSG_SIZE 2
#define MSG_SIZE 3

std::vector<uint8_t> ServerProtocol::recv_init_msg(bool &was_closed) {
    std::vector<uint8_t> data;
    uint8_t byte;
    for (int i = 0; i < INIT_MSG_SIZE; i++) {
        sk.recvall(&byte, sizeof(byte), &was_closed);
        data.push_back(byte);
    }
    return data;
}

void ServerProtocol::send_id(uint8_t id, bool &was_closed) {
    sk.sendall(&id, sizeof(id), &was_closed);
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

void ServerProtocol::send_msg(std::vector<uint8_t> &msg, bool &was_closed) {
    int size = msg.size();
    for (int i = 0; i < size; i++) {
        uint8_t byte = msg[i];
        sk.sendall(&byte, sizeof(byte), &was_closed);
    }
}

void ServerProtocol::send_game_data(QueueData &game_data, bool &was_closed) {
    if (std::holds_alternative<uint8_t>(game_data)) {
        uint8_t byte = std::get<uint8_t>(game_data);
        sk.sendall(&byte, sizeof(byte), &was_closed);
    } else {
        std::vector<uint8_t> bytes = encodeInfoJuego(std::get<InfoJuego>(game_data));
        sk.sendall(bytes.data(), bytes.size(), &was_closed);
    }
}

int ServerProtocol::disconnect() {
    sk.shutdown(SHUTCODE);
    sk.close();
    return SUCCESS;
}

//METODOS PRIVADOS

std::vector<uint8_t> ServerProtocol::encodeInfoJuego(const InfoJuego &infoJuego) {
    std::vector<uint8_t> bytes;

    int sz = infoJuego.getLengthData();

    uint8_t sz1 = (sz >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t sz2 = sz & 0xFF; // Obtener el byte menos significativo
    bytes.push_back(sz1);
    bytes.push_back(sz2);

    bytes.push_back(infoJuego.cantidadPlayers());
    for (int i=0; i < infoJuego.cantidadPlayers(); i++) {
        auto dataPlayer = encodePlayer(infoJuego.players[i]);
        bytes.insert(bytes.end(), dataPlayer.begin(), dataPlayer.end());//concateno
    }
    bytes.push_back(infoJuego.cantEnemigos());
    for (int i=0; i < infoJuego.cantEnemigos(); i++) {
        auto dataEnemigo = encodeEnemy(infoJuego.enemigos[i]);
        bytes.insert(bytes.end(), dataEnemigo.begin(), dataEnemigo.end());//concateno
    }
    bytes.push_back(infoJuego.cantRecolectables());
    for (int i=0; i < infoJuego.cantRecolectables(); i++) {
        auto dataRecolectable = encodeRecolectable(infoJuego.recolectables[i]);
        bytes.insert(bytes.end(), dataRecolectable.begin(), dataRecolectable.end());//concateno
    }
    bytes.push_back(infoJuego.cantProyectiles());
    for (int i=0; i < infoJuego.cantProyectiles(); i++) {
        auto dataProyectil = encodeProyectil(infoJuego.proyectiles[i]);
        bytes.insert(bytes.end(), dataProyectil.begin(), dataProyectil.end());//concateno
    }
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodePlayer(const InfoPlayer &infoPlayer) {
    std::vector<uint8_t> bytes;
    bytes.push_back(infoPlayer.id);
    
    int x = infoPlayer.pos_x;
    int y = infoPlayer.pos_y;
    uint8_t x1 = (x >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t x2 = x & 0xFF; // Obtener el byte menos significativo
    uint8_t y1 = (y >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t y2 = y & 0xFF; // Obtener el byte menos significativo

    bytes.push_back(x1);
    bytes.push_back(x2);
    bytes.push_back(y1);
    bytes.push_back(y2);
    
    bytes.push_back(infoPlayer.player_id);
    bytes.push_back(encodeEstadoPlayer(infoPlayer.estado));
    bytes.push_back(infoPlayer.vida);
    bytes.push_back(infoPlayer.puntos);
    bytes.push_back(ARMA_COMUN);
    bytes.push_back(infoPlayer.muncion);
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeEnemy(const InfoEnemigo &infoEnemigo) {
    std::vector<uint8_t> bytes;

    bytes.push_back(encodeTipoEnemy(infoEnemigo.tipo));

    int x = infoEnemigo.pos_x;
    int y = infoEnemigo.pos_y;
    uint8_t x1 = (x >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t x2 = x & 0xFF; // Obtener el byte menos significativo
    uint8_t y1 = (y >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t y2 = y & 0xFF; // Obtener el byte menos significativo

    bytes.push_back(x1);
    bytes.push_back(x2);
    bytes.push_back(y1);
    bytes.push_back(y2);
    bytes.push_back(encodeEstadoEnemy(infoEnemigo.estado));
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeRecolectable(const InfoRecolectable &infoItem) {
    std::vector<uint8_t> bytes;

    bytes.push_back(encodeTipoRecolectable(infoItem.tipo));
    int x = infoItem.pos_x;
    int y = infoItem.pos_y;
    uint8_t x1 = (x >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t x2 = x & 0xFF; // Obtener el byte menos significativo
    uint8_t y1 = (y >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t y2 = y & 0xFF; // Obtener el byte menos significativo

    bytes.push_back(x1);
    bytes.push_back(x2);
    bytes.push_back(y1);
    bytes.push_back(y2);
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeProyectil(const InfoProyectil &infoProyectil) {
    std::vector<uint8_t> bytes;

    int x = infoProyectil.pos_x;
    int y = infoProyectil.pos_y;
    uint8_t x1 = (x >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t x2 = x & 0xFF; // Obtener el byte menos significativo
    uint8_t y1 = (y >> 8) & 0xFF; // Obtener el byte más significativo
    uint8_t y2 = y & 0xFF; // Obtener el byte menos significativo

    bytes.push_back(x1);
    bytes.push_back(x2);
    bytes.push_back(y1);
    bytes.push_back(y2);
    bytes.push_back(encodeDireccion(infoProyectil.direccion));
    return bytes;
}

uint8_t ServerProtocol::encodeEstadoPlayer(EstadosPlayer estado) {
    switch (estado) {
        case EstadosPlayer::Inactive:
            return STATE_IDLE;
        case EstadosPlayer::Walking:
            return STATE_WALK;
        case EstadosPlayer::Running:
            return STATE_RUN;
        case EstadosPlayer::Jumping:
            return STATE_JUMP;
        case EstadosPlayer::Shooting:
            return STATE_SHOOT;
        case EstadosPlayer::SpecialAttack:
            return STATE_SPECIAL_ATTACK;
        default: 
            return STATE_IDLE;
    }
}

uint8_t ServerProtocol::encodeTipoEnemy(TipoEnemy enemigo) {
	switch (enemigo) {
        case Rat:
            return ENEMY_RAT;
        case Bat:
            return ENEMY_BAT;
        case Lizard:
            return ENEMY_LIZARD;	
        default:
            return ENEMY_RAT;
    }
}

uint8_t ServerProtocol::encodeEstadoEnemy(EstadosEnemy byte) {
	switch (byte) {
	    case EstadosEnemy::Idle: 
            return ENEMY_STATE_IDLE;
        case EstadosEnemy::Move:
            return ENEMY_STATE_MOVE;
	    case EstadosEnemy::Attack:
            return ENEMY_STATE_ATTACK;
	    case EstadosEnemy::Damaged:
            return ENEMY_STATE_DAMAGED;
	    case EstadosEnemy::Death:
            return ENEMY_STATE_DEATH;
	    default:
            return ENEMY_STATE_IDLE;
            //std::runtime_error("Estado de enemigo no existe.
                //Probablemente se recibio un byte que corresponde a ora cosa");
	}
}

uint8_t ServerProtocol::encodeTipoRecolectable(TipoRecolectable tipo){
    switch (tipo) {
        case TipoRecolectable::Diamante:
            return ITEM_DIAMANTE;
        case TipoRecolectable::Moneda:
            return ITEM_MONEDA;
        case TipoRecolectable::Zanahoria:
            return ITEM_ZANAHORIA;
        case TipoRecolectable::Municion:
            return ITEM_MUNCION;
        default:
            return ITEM_DIAMANTE;
    }
}

uint8_t ServerProtocol::encodeDireccion(Direcciones direccion) {
	switch (direccion) {
		case Left:
            return LEFT;
		case Right:
            return RIGHT;
		default: 
		    //throw std::runtime_error("ERROR. Direccion invalida");
		    return RIGHT;
	}
}

// Decodificicar
AccionesPlayer  ServerProtocol::decodeAction(uint8_t byte) {
    switch (byte) {
        case ACTION_IDLE:
            return AccionesPlayer::Idle;
        case ACTION_WALK:
            return AccionesPlayer::Walk;
        case ACTION_RUN: 
            return AccionesPlayer::Run;
        case ACTION_JUMP:
            return AccionesPlayer::Jump;
        case ACTION_SHOOT:
            return AccionesPlayer::Shoot;
        case ACTION_SPECIAL_ATACK:
            return AccionesPlayer::SpecialAttack;
        default:
            //Excepcion
            return AccionesPlayer::Idle;
    }
}

Direcciones ServerProtocol::decodeDireccion(uint8_t byte) {
    switch (byte) {
        case LEFT:
            return Direcciones::Left;
        case RIGHT:
            return Direcciones::Right;
        default:
            //Excepcion
            return Direcciones::Right;
    }
}
