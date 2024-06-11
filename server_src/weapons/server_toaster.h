#ifndef SERVER_TOASTER_H_
#define SERVER_TOASTER_H_

#include "server_weapon.h"
#include "projectile/server_toasterball.h"

class Toaster : public Weapon {
    private:

    public:
        Toaster(uint8_t current_ammo, std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = current_ammo;
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
            max_ammo = data[MA_POS];
        };
};
#endif
