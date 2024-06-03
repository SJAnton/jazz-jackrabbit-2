#include "game_object.h"

GameObject::GameObject(unsigned int w, unsigned int h) :
    width(w), height(h),
    position(0,0),
    pos_x_max(position.x + w -1),
    pos_y_max(position.y + h -1)
{

}

    
Coordenada GameObject::getPosition() {
    return position;
}
Coordenada GameObject::getPositionEnd() {
    return Coordenada(pos_x_max, pos_y_max);
}



void GameObject::setPosition(const Coordenada &coordenada) {
    position.x = coordenada.x;
    position.y = coordenada.y;
    pos_x_max = position.x + width -1;
    pos_y_max = position.y + height -1;
}

// Me dice si alguna parte del cuerpo del objeto esta dentro de la coordenada recibida
bool GameObject::isInside(const Coordenada &coordenada) {
    return (coordenada.x >= position.x && coordenada.x <= pos_x_max && 
            coordenada.y >= position.y && coordenada.y <= pos_y_max);
}

void GameObject::addGravity() {
    has_gravity = true;
}

std::vector<Coordenada> GameObject::coordenadasArriba() {
    std::vector<Coordenada> coordenadas;
    for (int i = position.x; i <= pos_x_max; i++) {
        coordenadas.emplace_back(i,position.y-1);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasAbajo() {
    std::vector<Coordenada> coordenadas;
    for (int i = position.x; i <= pos_x_max; i++)
    {
        coordenadas.emplace_back(i,position.y+1);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasIzquierda() {
    std::vector<Coordenada> coordenadas;
    for (int i = position.y; i <= pos_y_max; i++)
    {
        coordenadas.emplace_back(position.x-1, i);
    }
    return coordenadas;
}
std::vector<Coordenada> GameObject::coordenadasDerecha() {
    std::vector<Coordenada> coordenadas;
    for (int i = position.y; i <= pos_y_max; i++)
    {
        coordenadas.emplace_back(position.x+1, i);
    }
    return coordenadas;
}

std::vector<Coordenada> GameObject::coordenadasOcupadas() {
    std::vector<Coordenada> coordenadas;
        for (int i = position.x; i <= pos_x_max; i++) {
            for (int j = position.y; j <= pos_y_max; j++) {
                coordenadas.emplace_back(i, j);
            }
            
        }
        return coordenadas;
}

