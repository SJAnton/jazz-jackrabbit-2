#ifndef SPRITE_PROYECTIL_H
#define SPRITE_PROYECTIL_H


#include "spritesheet.h"
#include "sprites_players.h"
#include "../../common_src/constantes.h"



    int it = 0;
    



    void setPosition(int x, int y);

    void setFlip(bool flip);
    void setFlip(const Direcciones &dir);
    
    void setEstado(const EstadosPlayer &estado);

    EstadosPlayer getEstado();

    void renderizarEn(int x, int y);
    void renderizar();
    void updateFrame();

class SpriteProyectil
{
private:
    TipoArma tipo;
    SpriteSheet spriteSheet;
    Direcciones dir;

   
public:
    SpriteProyectil();
    ~SpriteProyectil();
};


#endif //SPRITE_PROYECTIL_H
