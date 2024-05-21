#ifndef SERVER_BLASTER_H_
#define SERVER_BLASTER_H_

#include "server_weapon.h"
#include "projectile/server_blasterball.h"

#define NAME "Blaster"
#define AMMO -1
#define FR_POS 0
#define RC_POS 1
#define SP_POS 2

class Blaster : public Weapon {
    private:
        std::string name = NAME;

        uint8_t ammo = AMMO;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

        std::vector<uint8_t> &data;

    public:
        Blaster(std::vector<uint8_t> &data) : data(data) {
            fire_rate = data[FR_POS];
            recharge_cooldown = data[RC_POS];
            projectile_speed = data[SP_POS];
        }

        void shoot(); //override
};  
#endif
