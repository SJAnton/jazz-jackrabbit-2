#include "game_object_player.h"


ObjectPlayer::ObjectPlayer(int id) :
    GameObject(WIDTH_PLAYER, HEIGHT_PLAYER),
    player_id(id)
{
    type = TypeGameObject::Player;
}

// Movimientos
void ObjectPlayer::walk(Direcciones direccion) {
    if (direccion == Left)
        move(position.x - x_hitbox, position.y);
    else if (direccion == Right)
        move(position.x + x_hitbox, position.y);
}

void ObjectPlayer::fall() {
        move(position.x, position.y + 1);
}

// setters
void ObjectPlayer::add_points(int points) {
    this->points += points;
}

//Metodos privados:
void ObjectPlayer::move(unsigned x, unsigned int y) {
    position.x = x;
    position.y = y;
    pos_x_max = x + width;
    pos_y_max = y + height;
}

