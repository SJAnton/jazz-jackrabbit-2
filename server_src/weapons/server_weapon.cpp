#include "server_weapon.h"

bool Weapon::shoot() {
    if (ammo > 0) {
        ammo--;
        return true;
    }
    return false;
}

uint8_t Weapon::get_id() {
    return weapon_id;
}

uint8_t Weapon::get_ammo() {
    return ammo;
}
