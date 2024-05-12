#include "server_freezer.h"
#include "projectile/server_iceball.h"

#include <string>
#include <cstdint>


void Freezer::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Iceball(x, y);
    ammo--;
    return;
}