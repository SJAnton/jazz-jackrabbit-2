#include "server_rf_missile.h"
#include "projectile/server_rocket.h"

#include <string>
#include <cstdint>


void RFMissile::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Rocket(x, y, data);
    ammo--;
    return;
}