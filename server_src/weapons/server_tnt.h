#ifndef SERVER_TNT_H_
#define SERVER_TNT_H_

#include "server_weapon.h"

#define NAME "TNT"
#define AM_POS 0
#define RD_POS 1
#define RC_POS 2

class TNT : public Weapon {
    private:
        std::string name = NAME;

        uint8_t ammo;

        uint8_t radius;

        uint8_t recharge_cooldown;

        std::vector<uint8_t> &data;

    public:
        TNT(std::vector<uint8_t> &data) : data(data) {
            ammo = data[AM_POS];
            radius = data[RD_POS];
            recharge_cooldown = data[RC_POS];
        }

        void shoot(); //override
};
#endif