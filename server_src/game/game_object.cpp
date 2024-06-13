#include "game_object.h"
#include <iostream>

GameObject::GameObject(unsigned int w, unsigned int h) :
    position(0,0),
    width(w), height(h)
    //pos_x_max(position.x + w -1),
    //pos_y_max(position.y + h -1),
    //x_left(position.x -1),
    //x_right(pos_x_max +1),
    //y_up(position.y -1),
    //y_down(pos_y_max +1)
{
   if (position.x >= 1) {
        x_left = position.x - 1;
    } else {
        x_left = 0;
    }

    if (position.y >= 1) {
        y_up = position.y - 1;
    } else {
        y_up = 0;
    }
    pos_x_max = position.x + width - 1;
    pos_y_max = position.y + height - 1;
    x_right = pos_x_max + 1;
    y_down = pos_y_max + 1;
}


Coordenada GameObject::getPosition() {
    return position;
}
Coordenada GameObject::getPositionEnd() {
    return Coordenada(pos_x_max, pos_y_max);
}



void GameObject::setPosition(const Coordenada &coordenada) {
    if (coordenada.x > X_MAX) {
        return;
    }

    position.x = coordenada.x;
    position.y = coordenada.y;
    pos_x_max = position.x + width -1;
    pos_y_max = position.y + height -1;

    x_left = position.x -1;
    x_right = pos_x_max +1;
    y_up = position.y -1;
    y_down = pos_y_max +1;

    if (position.x > X_MAX) 
        x_left = 0;
    if (position.y < 1)
        y_up = 0;
}

void GameObject::set_pos_x(int x) {
    if (x < 0)
        return;
    position.x = x;
    pos_x_max = position.x + width -1;
    x_left = position.x -1;
    x_right = pos_x_max +1;
    if (position.x < 1) 
        x_left = 0;
    if (position.y < 1)
        y_up = 0;
}
bool GameObject::isInside(const Coordenada &coordenada) {
    return (coordenada.x >= position.x && coordenada.x <= pos_x_max && 
            coordenada.y >= position.y && coordenada.y <= pos_y_max);
}

void GameObject::addGravity() {
    has_gravity = true;
}

std::vector<Coordenada> GameObject::coordenadasUp() {
    std::vector<Coordenada> coordenadas;
    for (auto i = position.x; i <= pos_x_max; i++) {
        coordenadas.emplace_back(i,position.y-1);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasDown() {
    std::vector<Coordenada> coordenadas;
    for (auto i = position.x; i <= pos_x_max; i++) {
        coordenadas.emplace_back(i,position.y+1);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasLeft() {
    std::vector<Coordenada> coordenadas;
    for (auto i = position.y; i <= pos_y_max; i++) {
        coordenadas.emplace_back(position.x-1, i);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasRight() {
    std::vector<Coordenada> coordenadas;
    for (auto i = position.y; i <= pos_y_max; i++) {
        coordenadas.emplace_back(position.x+1, i);
    }
    return coordenadas;
}

std::vector<Coordenada> GameObject::coordenadasOcupadas() {
    std::vector<Coordenada> coordenadas;
    for (auto i = position.x; i <= pos_x_max; i++) {
        for (auto j = position.y; j <= pos_y_max; j++) {
            coordenadas.emplace_back(i, j);
        }
        
    }
    return coordenadas;
}
