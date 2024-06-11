#ifndef SERVER_RF_MISSILE_H_
#define SERVER_RF_MISSILE_H_

#include "server_weapon.h"
#include "projectile/server_rocket.h"

class RFMissile : public Weapon {
    private:

    public:
        RFMissile(uint8_t current_ammo, std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = current_ammo;
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
            max_ammo = data[MA_POS];
        };
};
#endif
