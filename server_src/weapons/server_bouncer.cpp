#include "server_bouncer.h"
#include "projectile/server_bouncerball.h"

#include <string>
#include <cstdint>


void Bouncer::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Bouncerball(x, y);
    ammo--;
    return;
}