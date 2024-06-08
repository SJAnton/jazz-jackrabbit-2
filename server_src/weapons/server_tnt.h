#ifndef SERVER_TNT_H_
#define SERVER_TNT_H_

#include "server_weapon.h"

#define TNT_ID_POS 0
#define TNT_AM_POS 1
#define TNT_RD_POS 2
#define TNT_RC_POS 3

class TNT : public Weapon {
    private:
        uint8_t weapon_id;

        uint8_t ammo;

        uint8_t radius;

        uint8_t recharge_cooldown;

        std::vector<uint8_t> &data;

    public:
        TNT(std::vector<uint8_t> &data) : data(data) {
            weapon_id = data[TNT_ID_POS];
            ammo = data[TNT_AM_POS];
            radius = data[TNT_RD_POS];
            recharge_cooldown = data[TNT_RC_POS];
        }
};
#endif
