#include "server_toaster.h"
#include "projectile/server_toasterball.h"

#include <string>
#include <cstdint>


void Toaster::shoot() {
    // Shoot implementation
    
    // Esto se va a borrar cuando saquemos la ubicacion real del jugador
    uint8_t x = 0;
    uint8_t y = 0;

    new Toasterball(x, y, data);
    ammo--;
    return;
}