#ifndef SPRITE_PLAYER_H
#define SPRITE_PLAYER_H

#include "spritesheet.h"
#include "sprites_players.h"
#include "../../common_src/constantes.h"

class SpritePlayer {
private:
    int id; // Para poder identificarlos en el caso de necesitarlo
    TipoPlayer tipo;
    SpriteSheet spriteSheet;
    EstadosPlayer estado = EstadosPlayer::Inactive;
    Position position;
    bool flip = false; //es true cuando está mirando a la izquierda
    int it = 0;

private:
    void setEstadoSpaz(const EstadosPlayer &estado_);
    void setEstadoJazz(const EstadosPlayer &estado_);
    void setEstadoLori(const EstadosPlayer &estado_);

public:
    SpritePlayer(int id, TipoPlayer tipoPlayer);

    void setPosition(int x, int y);
    void setFlip(const Direcciones &dir);    
    void setEstado(const EstadosPlayer &estado);

    EstadosPlayer getEstado();
    int getId();

    void renderizarEn(int x, int y);
    void renderizar();
    void updateFrame();
    
    //~SpritePlayer();
};

#endif
