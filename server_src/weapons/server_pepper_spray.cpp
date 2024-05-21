#include "server_pepper_spray.h"
#include "projectile/server_fireball.h"

#include <string>
#include <cstdint>


void PepperSpray::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Fireball(x, y, data);
    ammo--;
    return;
}