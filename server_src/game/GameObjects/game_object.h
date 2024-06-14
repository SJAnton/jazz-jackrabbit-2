#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../game_coordenada.h"
//#include "../game_mundo.h"

#include "../../../common_src/info_juego.h"

#include <vector>

#define X_MAX 30*64

class GameMundo; // Declaración anticipada de GameMundo


enum TypeGameObject {Player, Collected, Enemy, Proyectil, Default};

/**
 * Un game object es un rectangulo que representa un objeto con cuerpo del juego, 
 * donde 'position' corresponde al vertice superior izquierdo de su rectángulo
 * 
 * Es la clase base de la que heredarán todos los objetos del juego como Player, Enemy, Item, etc.
*/
class GameObject
{
protected:
    TypeGameObject type;
    Coordenada position;// (en el sistema de coordenadas del juego)

    unsigned int width; // Cantidad de unidades (a la derecha de pos_x) que ocupa el cuerpo de ancho 
    unsigned int height; // Cantidad de unidades (debajo de pos_y) que ocupa el largo del cuerpo

    unsigned int pos_x_max; //position.x + width
    unsigned int pos_y_max; //position.y + height
    
    unsigned int x_left; //x -1
    unsigned int x_right; //x_max +1
    unsigned int y_up; // y - 1
    unsigned int y_down; // y_max + 1

    bool has_gravity = false;

    void set_pos_x(int x);

public:
    GameObject(unsigned int width, unsigned int height);

    
    Coordenada getPosition();

    // Devuelve el vertice opuesto al de 'position' (esquina inferior derecha)
    Coordenada getPositionEnd();

    TypeGameObject getType() {return type;};

    void setPosition(const Coordenada &coordenada);
    
    // Establece el objeto "con gravedad"
    void addGravity();

    // Me dice si alguna parte del cuerpo del objeto esta dentro de la coordenada recibida
    bool isInside(const Coordenada &coordenada);

    bool haveGravity() {return has_gravity;};

   
    // Devuelve una lista con las coordenadas de los alrededores
    std::vector<Coordenada> coordenadasUp();
    std::vector<Coordenada> coordenadasDown();
    std::vector<Coordenada> coordenadasLeft();
    std::vector<Coordenada> coordenadasRight();

    // Devuelve una lista con las coordenadas ocupadas por el cuerpo del GameObject
    std::vector<Coordenada> coordenadasOcupadas();

};


#endif //GAME_OBJECT_H