#ifndef SERVER_SEEKER_H_
#define SERVER_SEEKER_H_

#include "server_weapon.h"
#include "projectile/server_seeker_rocket.h"

class Seeker : public Weapon {
    private:

    public:
        Seeker(std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
        };
};
#endif
