#ifndef SERVER_BLASTER_H_
#define SERVER_BLASTER_H_

#include "server_weapon.h"
#include "projectile/server_blasterball.h"

#define AMMO 0
#define BL_ID_POS 0
#define BL_FR_POS 1
#define BL_RC_POS 2

class Blaster : public Weapon {
    private:
        uint8_t ammo = AMMO;

    public:
        Blaster(std::vector<uint8_t> &data) {
            weapon_id = data[BL_ID_POS];
            fire_rate = data[BL_FR_POS];
            cooldown = data[BL_RC_POS];
        }

        bool shoot() override;
};  
#endif
