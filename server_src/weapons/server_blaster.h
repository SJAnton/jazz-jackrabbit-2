#ifndef SERVER_BLASTER_H_
#define SERVER_BLASTER_H_

#include "server_weapon.h"
#include "projectile/server_blasterball.h"

#define AMMO -1
#define BL_ID_POS 0
#define BL_FR_POS 1
#define BL_RC_POS 2
#define BL_SP_POS 3

class Blaster : public Weapon {
    private:
        uint8_t weapon_id;

        uint8_t ammo = AMMO;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

        std::vector<uint8_t> &data;

    public:
        Blaster(std::vector<uint8_t> &data) : data(data) {
            weapon_id = data[BL_ID_POS];
            fire_rate = data[BL_FR_POS];
            recharge_cooldown = data[BL_RC_POS];
            projectile_speed = data[BL_SP_POS];
        }

        void shoot(); //override
};  
#endif
