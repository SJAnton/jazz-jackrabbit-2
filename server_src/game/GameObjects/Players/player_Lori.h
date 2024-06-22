#ifndef PLAYER_LORI_H
#define PLAYER_LORI_H

#include "game_object_player.h"

#define TIME_HIGHKICK 20

class PlayerLori : public ObjectPlayer
{
private:

public:
    PlayerLori(int id);

    /**
     * Inicia el ataque 'highkick' (una patada donde se desplaza en el eje y)
    */
    void specialAttack() override;

    void updateSpecialAttack() override;

};



#endif 
