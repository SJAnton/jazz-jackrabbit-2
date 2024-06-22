#ifndef PLAYER_SPAZ_H
#define PLAYER_SPAZ_H

#include "game_object_player.h"

#define TIME_SIDEKECK 24

class PlayerSpaz : public ObjectPlayer
{
private:

public:
    PlayerSpaz(int id);

    /**
     * Inicia el ataque 'sidekick' (una patada donde se desplaza en el eje x)
    */
    void specialAttack() override;

    void updateSpecialAttack() override;

};



#endif 
