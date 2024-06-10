#ifndef SERVER_TOASTER_H_
#define SERVER_TOASTER_H_

#include "server_weapon.h"
#include "projectile/server_toasterball.h"

class Toaster : public Weapon {
    private:

    public:
        Toaster(std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
        };
};
#endif
