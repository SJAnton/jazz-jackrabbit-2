#ifndef SERVER_TNT_H_
#define SERVER_TNT_H_

#include "server_weapon.h"

#define TNT_RD_POS 2

class TNT : public Weapon {
    private:
        uint8_t radius;

    public:
        TNT(uint8_t current_ammo, std::vector<uint8_t> &data) {
            weapon_id = data[ID_POS];
            ammo = current_ammo;
            radius = data[TNT_RD_POS];
            cooldown = data[RC_POS];
            max_ammo = data[MA_POS];
        }
};
#endif
