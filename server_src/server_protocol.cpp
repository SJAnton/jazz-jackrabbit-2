#include "server_protocol.h"

#include <iostream>
#include <iomanip>

#define SUCCESS 0
#define SHUTCODE 2

#define INIT_MSG_SIZE 2

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
    for (int i = 0; i < SIZE_CLIENT_MSG; i++) {
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

void ServerProtocol::send_game_data(InfoJuego &game_data, bool &was_closed) {
    std::vector<uint8_t> bytes = encodeInfoJuego(game_data);
    sk.sendall(bytes.data(), bytes.size(), &was_closed);
    //std::cout <<"was_closed: "<< was_closed << std::endl;
}

int ServerProtocol::disconnect() {
    sk.shutdown(SHUTCODE);
    sk.close();
    return SUCCESS;
}

//METODOS PRIVADOS

std::vector<uint8_t> ServerProtocol::encodeInfoJuego(const InfoJuego &infoJuego) {
    std::vector<uint8_t> bytes;
    
    insertar2bytesDelNumero(infoJuego.getLengthData(), bytes);   
    bytes.push_back(infoJuego.cantidadPlayers());
    //std::cout << "cant players " << infoJuego.cantidadPlayers() << std::endl;
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
    /*std::cout << "Mensaje enviado: ";
		for (uint8_t byte : bytes) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
		}
		std::cout << std::endl;
        */
    return bytes;
}


std::vector<uint8_t> ServerProtocol::encodePlayer(const InfoPlayer &infoPlayer) {
    std::vector<uint8_t> bytes;
    bytes.push_back(infoPlayer.id);
    insertar2bytesDelNumero(infoPlayer.pos_x, bytes);
    insertar2bytesDelNumero(infoPlayer.pos_y, bytes);
    bytes.push_back(encodeDireccion(infoPlayer.direccion));
    bytes.push_back(encodeTipoPlayer(infoPlayer.tipoPlayer));
    bytes.push_back(encodeEstadoPlayer(infoPlayer.estado));
    bytes.push_back(infoPlayer.vida);
    bytes.push_back(infoPlayer.puntos);
    bytes.push_back(encodeTipoArma(infoPlayer.arma));
    bytes.push_back(infoPlayer.municion);
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeEnemy(const InfoEnemigo &infoEnemigo) {
    std::vector<uint8_t> bytes;

    bytes.push_back(encodeTipoEnemy(infoEnemigo.tipo));

    insertar2bytesDelNumero(infoEnemigo.pos_x, bytes);
    insertar2bytesDelNumero(infoEnemigo.pos_y, bytes);
    bytes.push_back(encodeDireccion(infoEnemigo.direccion));
    bytes.push_back(encodeEstadoEnemy(infoEnemigo.estado));
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeRecolectable(const InfoRecolectable &infoItem) {
    std::vector<uint8_t> bytes;

    bytes.push_back(encodeTipoRecolectable(infoItem.tipo));

    insertar2bytesDelNumero(infoItem.pos_x, bytes);
    insertar2bytesDelNumero(infoItem.pos_y, bytes);
    return bytes;
}

std::vector<uint8_t> ServerProtocol::encodeProyectil(const InfoProyectil &infoProyectil) {
    std::vector<uint8_t> bytes;
    bytes.push_back(encodeTipoArma(infoProyectil.tipo));
    insertar2bytesDelNumero(infoProyectil.pos_x, bytes);
    insertar2bytesDelNumero(infoProyectil.pos_y, bytes);

    bytes.push_back(encodeDireccion(infoProyectil.direccion));
    return bytes;
}

void ServerProtocol::insertar2bytesDelNumero(int num, std::vector<uint8_t> &array) {
    int aux = htons(num);
    array.push_back((aux >> 8) & 0xFF); // insertar el byte más significativo
    array.push_back(aux & 0xFF); // inseratr el byte menos significativo
}

// Codificadores
/*
uint8_t ServerProtocol::encodeTipoPlayer(TipoPlayer tipo) {
	switch (tipo)
	{
	case Jazz : return PLAYER_TYPE_JAZZ;
	case Lori : return PLAYER_TYPE_LORI;
	case Spaz : return PLAYER_TYPE_SPAZ;	
	default:
        std::invalid_argument("En ServerProtocol::encodeTipoPlayer()");
		return PLAYER_TYPE_JAZZ;
	}
}


uint8_t ServerProtocol::encodeEstadoPlayer(const EstadosPlayer &estado) {
    switch (estado) {
        case EstadosPlayer::Inactive: return STATE_IDLE;
        case EstadosPlayer::Walking: return STATE_WALK;
        case EstadosPlayer::Running: return STATE_RUN;
        case EstadosPlayer::Jumping: return STATE_JUMP;
        case EstadosPlayer::Falling: return STATE_FALL;
        case EstadosPlayer::Shooting: return STATE_SHOOT;
        case EstadosPlayer::SpecialAttack: return STATE_SPECIAL_ATTACK;
        case EstadosPlayer::IntoxicatedIdle: return STATE_INTOXICATED_IDLE;
        case EstadosPlayer::IntoxicatedWalk: return STATE_INTOXICATED_WALK;
        case EstadosPlayer::Damaged: return STATE_DAMAGED;
        case EstadosPlayer::Dying: return STATE_DYING;
        case EstadosPlayer::Dead: return STATE_DEAD;
        case EstadosPlayer::Reviving: return STATE_REVIVE;
        default: 
            std::invalid_argument("En ServerProtocol::encodeEstadoPlayer()");
            return STATE_IDLE;
    }
}

uint8_t ServerProtocol::encodeTipoEnemy(TipoEnemy enemigo) {
	switch (enemigo) {
        case Rat: return ENEMY_RAT;
        case Bat: return ENEMY_BAT;
        case Lizard: return ENEMY_LIZARD;	
        default:
            std::invalid_argument("En ServerProtocol::encodeTipoEnemy()");
            return ENEMY_RAT;
    }
}

uint8_t ServerProtocol::encodeEstadoEnemy(EstadosEnemy byte) {
	switch (byte) {
	    case EstadosEnemy::Idle: return ENEMY_STATE_IDLE;
        case EstadosEnemy::Move: return ENEMY_STATE_MOVE;
	    case EstadosEnemy::Attack: return ENEMY_STATE_ATTACK;
	    case EstadosEnemy::Damaged: return ENEMY_STATE_DAMAGED;
	    case EstadosEnemy::Death: return ENEMY_STATE_DEATH;
	    default:
            std::invalid_argument("En ServerProtocol::encodeEstadoEnemy()");
            return ENEMY_STATE_IDLE;
	}
}

uint8_t ServerProtocol::encodeTipoRecolectable(TipoRecolectable tipo){
    switch (tipo) {
        case Diamante: return ITEM_DIAMANTE;
        case Moneda:   return ITEM_MONEDA;
        case Zanahoria: return ITEM_ZANAHORIA;
        case Municion: return ITEM_MUNCION;
        default:
            std::invalid_argument("En ServerProtocol::encodeTipoRecolectable()");
            return ITEM_DIAMANTE;
    }
}

uint8_t ServerProtocol::encodeDireccion(Direcciones direccion) {
	switch (direccion) {
		case Left: return LEFT;
		case Right: return RIGHT;
		default: 
            std::invalid_argument("En ServerProtocol::encodeDireccion()");
		    return RIGHT;
	}
}

AccionesPlayer  ServerProtocol::decodeAction(uint8_t byte) {
    switch (byte) {
        case ACTION_IDLE: return AccionesPlayer::Idle;
        case ACTION_WALK: return AccionesPlayer::Walk;
        case ACTION_RUN: return AccionesPlayer::Run;
        case ACTION_JUMP: return AccionesPlayer::Jump;
        case ACTION_SHOOT: return AccionesPlayer::Shoot;
        case ACTION_SPECIAL_ATTACK: return AccionesPlayer::SpecialAttack;
        default:
            std::invalid_argument("En ServerProtocol::encodeAction()");
            return AccionesPlayer::Idle;
    }
}

Direcciones ServerProtocol::decodeDireccion(uint8_t byte) {
    switch (byte) {
        case LEFT: return Direcciones::Left;
        case RIGHT: return Direcciones::Right;
        default:
            std::invalid_argument("En ServerProtocol::decodeDireccion()");
            return Direcciones::Right;
    }
}
*/
