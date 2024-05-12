#include "server_blaster.h"
#include "projectile/server_blasterball.h"

#include <string>
#include <cstdint>


void Blaster::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Blasterball(x, y);
    return;
}