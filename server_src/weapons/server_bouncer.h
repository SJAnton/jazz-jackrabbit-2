#ifndef SERVER_BOUNCER_H_
#define SERVER_BOUNCER_H_

#include "server_weapon.h"
#include "projectile/server_bouncerball.h"

class Bouncer : public Weapon {
    private:

    public:
        Bouncer(std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
        };
};
#endif
