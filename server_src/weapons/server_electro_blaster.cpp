#include "server_electro_blaster.h"
#include "projectile/server_electroball.h"

#include <string>
#include <cstdint>


void ElectroBlaster::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Electroball(x, y, data);
    ammo--;
    return;
}