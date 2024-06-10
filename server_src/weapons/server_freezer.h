#ifndef SERVER_FREEZER_H_
#define SERVER_FREEZER_H_

#include "server_weapon.h"
#include "projectile/server_iceball.h"

class Freezer : public Weapon {
    private:

    public:
        Freezer(std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
        };
};
#endif
