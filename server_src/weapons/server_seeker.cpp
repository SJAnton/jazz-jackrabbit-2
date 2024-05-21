#include "server_seeker.h"
#include "projectile/server_seeker_rocket.h"

#include <string>
#include <cstdint>


void Seeker::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new SeekerRocket(x, y, data);
    ammo--;
    return;
}