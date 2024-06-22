#include "game_object_projectile.h"
#include "../../game_mundo.h"
#include <iostream>


// Inicialización de las variables estáticas (sin valor inicial explícito)
// (es un tema de compilacion. Confiar)
bool ObjectProjectile::inizializated = false;
int ObjectProjectile::damage_p1 = 0;
int ObjectProjectile::damage_p2 = 0;
int ObjectProjectile::damage_p3 = 0;
int ObjectProjectile::damage_p4 = 0;
int ObjectProjectile::speed_p1 = 0;
int ObjectProjectile::speed_p2 = 0;
int ObjectProjectile::speed_p3 = 0;
int ObjectProjectile::speed_p4 = 0;

//Inicializo todas las constantes una unica vez
void ObjectProjectile::init(int damage_p1, int damage_p2, int damage_p3, int damage_p4,
                            int speed_p1, int speed_p2, int speed_p3, int speed_p4) {
    if (!inizializated) {
        ObjectProjectile::damage_p1 = damage_p1;
        ObjectProjectile::damage_p2 = damage_p2;
        ObjectProjectile::damage_p3 = damage_p3;
        ObjectProjectile::damage_p4 = damage_p4;
        ObjectProjectile::speed_p1 = speed_p1;
        ObjectProjectile::speed_p2 = speed_p2;
        ObjectProjectile::speed_p3 = speed_p3;
        ObjectProjectile::speed_p4 = speed_p4;
        inizializated = true;
    } else {
        //throw " Se quiso volver a inicializar las constantes de ObjectProjectile, que ya fueron inicializadas anteriormente"
    }
   
}


ObjectProjectile::ObjectProjectile(TipoArma tipo, const Direcciones &dir, const Coordenada &pos,
                                    std::shared_ptr<ObjectPlayer> &shooter) :
    GameObject(WIDTH_PROJECTILE, HEIGHT_PROJECTILE),
    tipoProyectil(tipo), direction(dir), shooter(shooter)
{
    type = TypeGameObject::Proyectil;

    switch (tipo)
    {
    case Tipo_1:
        this->damage = damage_p1;
        this->speed = speed_p1;
        break;
    case Tipo_2:
        this->damage = damage_p2;
        this->speed = speed_p2;
        break;
    case Tipo_3:
        this->damage = damage_p3;
        this->speed = speed_p3;
        break;
    case Tipo_4:
        this->damage = damage_p4;
        this->speed = speed_p4;
        break;
    default:
        throw std::invalid_argument("Error al construir ObjectProjectile. El tipo recibido no es válido.");
        break;
    }
    setPosition(pos);
}

void ObjectProjectile::move_x_pos() {
    if (direction == Left) {
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (position.x -1 <= 0 || position.x >= X_MAX) {
                explode(); //me fui de rango
                return;
            }
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (GameMundo::casilleros[position.y][x_left].estaBloqueado() || 
                GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()) { 
                //Colison con pared
                explode();
                return;
            } else {
                set_pos_x(position.x - 1);
            }
        }
    } else { //Right
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (position.x -1 <= 0 || position.x >= X_MAX) {
                explode(); //me fui de rango
                return;
            }
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (GameMundo::casilleros[position.y][x_right].estaBloqueado() || 
                GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()) { 
                //Colison con pared
                explode();
                return;
            } else {                
                set_pos_x(position.x + 1);
            }
        }
    }
}

int ObjectProjectile::explode() {
    exploded = true;
    return damage;
}

bool ObjectProjectile::is_exploded() {
    return exploded;
}

std::shared_ptr<ObjectPlayer> ObjectProjectile::get_shooter() {
    return shooter;
}

InfoProyectil ObjectProjectile::getInfo() {
    return InfoProyectil(tipoProyectil, position.x, position.y, direction);
}
