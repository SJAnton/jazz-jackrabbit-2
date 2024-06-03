#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_coordenada.h"

#include <vector>

enum TypeGameObject {Player, Collected, Enemy, Proyectil, Default};

/**
 * Un game object es un rectangulo, 
 * donde 'position' corresponde al vertice superior izquierdo
 * 
*/
class GameObject
{
protected:
    TypeGameObject type;
    Coordenada position;// (en el sistema de coordenadas del juego)

    unsigned int pos_x_max; //position.x + width
    unsigned int pos_y_max; //position.y + height

    unsigned int width; // Cantidad de unidades (a la derecha de pos_x) que ocupa el cuerpo de ancho 
    unsigned int height; // Cantidad de unidades (debajo de pos_y) que ocupa el largo del cuerpo

    bool has_gravity = false;
public:
    GameObject(unsigned int width, unsigned int height);

    
    Coordenada getPosition();

    // Devuelve el vertice opuesto al de 'position' (esquina inferior derecha)
    Coordenada getPositionEnd();

    TypeGameObject getType() {return type;};
    void setPosition(const Coordenada &coordenada);
    
    void addGravity();

    // Me dice si alguna parte del cuerpo del objeto esta dentro de la coordenada recibida
    bool isInside(const Coordenada &coordenada);
    bool haveGravity() {return has_gravity;};

   // int left_side(); // Devuelve x_pos - hitbox_x

    //int right_side(); // Devuelve x_pos + hitbox_x

//    int upper_side(); // Devuelve y_pos + hitbox_y

  //  int lower_side(); // Devuelve y_pos - hitbox_y

    // Devuelve una lista cn las coordenadas de los coordenadas de los alrededores
    std::vector<Coordenada> coordenadasArriba();
    std::vector<Coordenada> coordenadasAbajo();
    std::vector<Coordenada> coordenadasIzquierda();
    std::vector<Coordenada> coordenadasDerecha();

    std::vector<Coordenada> coordenadasOcupadas();

};


#endif //GAME_OBJECT_H
