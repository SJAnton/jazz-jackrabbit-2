#ifndef PLAYER_JAZZ_H
#define PLAYER_JAZZ_H

#include "game_object_player.h"

#define TIME_UPPERCUT 22

class PlayerJazz : public ObjectPlayer
{
private:

public:
    PlayerJazz(int id);

    /**
     * Inicia el ataque 'uppercut' (una puñetazo hacia arriba donde se desplaza en el eje y)
    */
    void specialAttack() override;

    void updateSpecialAttack() override;

};



#endif 
