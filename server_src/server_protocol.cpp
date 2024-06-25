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

std::string ServerProtocol::recv_chosen_level(bool &was_closed) {
    uint8_t length;
    std::string level_name;
    sk.recvall(&length, sizeof(length), &was_closed);
    for (int i = 0; i < length; ++i) {
        char c;
        sk.recvall(&c, sizeof(c), &was_closed);
        level_name += c;
    }
    return level_name;
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

void ServerProtocol::send_msg(
    std::vector<uint8_t> &msg, std::map<std::string, Level> &levels, bool &was_closed
) {
    int size = msg.size();
    for (int i = 0; i < size; i++) {
        uint8_t byte = msg[i];
        sk.sendall(&byte, sizeof(byte), &was_closed);
    }
    uint8_t lvls_size = levels.size();
    sk.sendall(&lvls_size, sizeof(lvls_size), &was_closed); // Cantidad de niveles
    for (auto &level : levels) {
        std::string name = level.first;
        uint8_t length = name.length(); // Longitud del nombre del nivel
        sk.sendall(&length, sizeof(length), &was_closed);
        for (char c : name) {
            sk.sendall(&c, sizeof(c), &was_closed);
        }
    }
}

void ServerProtocol::send_game_data(InfoJuego &game_data, bool &was_closed) {
    std::vector<uint8_t> bytes = encodeInfoJuego(game_data);
    sk.sendall(bytes.data(), bytes.size(), &was_closed);
    //std::cout <<"was_closed: "<< was_closed << std::endl;
}

void ServerProtocol::send_tile_map(TileMap &tile_map, bool &was_closed) {
    std::vector<uint8_t> bytes = tile_map.toBytes();
    sk.sendall(bytes.data(), bytes.size(), &was_closed);
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

    //agrego top 3
    int aux = infoJuego.rankingPlayers.size();
    bytes.push_back(aux);
    for (int i=0; i < aux; i++) {
        auto dataTabla = encodeTabla(infoJuego.rankingPlayers[i]);
        bytes.insert(bytes.end(), dataTabla.begin(), dataTabla.end());//concateno
    }

    //agrego teimpo restante
    insertar2bytesDelNumero(infoJuego.tiempo_restante, bytes); 

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
    //bytes.push_back(infoPlayer.puntos);
    insertar2bytesDelNumero(infoPlayer.puntos, bytes);
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

std::vector<uint8_t> ServerProtocol::encodeTabla(const InfoTabla &infoTabla) {
    std::vector<uint8_t> bytes;
    bytes.push_back(infoTabla.id);
    bytes.push_back(encodeTipoPlayer(infoTabla.tipoPlayer));
    insertar2bytesDelNumero(infoTabla.puntos, bytes);

    return bytes;
}


std::vector<uint8_t> ServerProtocol::encodeTileMap(TileMap &tileMap) {
    std::vector<uint8_t> bytes = tileMap.toBytes();
    return bytes;
}

void ServerProtocol::insertar2bytesDelNumero(int num, std::vector<uint8_t> &array) {
    int aux = htons(num);
    array.push_back((aux >> 8) & 0xFF); // insertar el byte más significativo
    array.push_back(aux & 0xFF); // inseratr el byte menos significativo
}
