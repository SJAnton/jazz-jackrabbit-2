#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include "spritesheet.h"
#include "../common_src/constantes.h"

class Player
{
private:
    TipoPlayer tipo;
    SpriteSheet spriteSheet;
    EstadosPlayer estado;
    Position position;
    bool flip = false; //es true cuando está mirando a la izquierda

public:
    Player(TipoPlayer TipoPlayer);

    void setPosition(int x, int y);

    void setFlip(bool flip);
    
    void setEstado(EstadosPlayer estado);
    EstadosPlayer getEstado();

    ~Player();
};

#endif
