#ifndef SPRITE_ENEMY_H
#define SPRITE_ENEMY_H

#include "spritesheet.h"
#include "sprites_enemies.h"
#include "../../common_src/constantes.h"

class SpriteEnemy {
private:
    TipoEnemy tipo;
    SpriteSheet spriteSheet;
    EstadosEnemy estado = EstadosEnemy::Idle;
    Position position;
    bool flip = false; //es true cuando está mirando a la izquierda
    int it = 0;

private:
    void setEstadoRat(const EstadosEnemy &estado_);
    void setEstadoBat(const EstadosEnemy &estado_);
    void setEstadoDiablo(const EstadosEnemy &estado_);

public:
    SpriteEnemy(TipoEnemy tipoEnemy);

    void setPosition(int x, int y);

    void setFlip(bool flip);
    void setFlip(const Direcciones &dir);
    
    void setEstado(const EstadosEnemy &estado);

    EstadosEnemy getEstado();

    void renderizarEn(int x, int y);
    void renderizar();
    void updateFrame();
    
    //~SpriteEnemy();
};

#endif