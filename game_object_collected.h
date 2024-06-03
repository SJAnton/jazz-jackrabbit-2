#ifndef OBJECT_COLLECTED_H
#define OBJECT_COLLECTED_H

#include "game_object.h"
#include "constantes.h"

//Estos valores se deben fijar en el config yaml
#define PTS_DIAMANTE 30
#define PTS_MONEDA 15
#define PTS_VIDA 1
#define PTS_MUNICION 10

#define WIDTH_COLLECTED 3
#define HEIGHT_COLLECTED 3

//enum TipoRecolectable {Moneda, Diamante, Zanahoria, Municion};

class ObjectCollected : public GameObject
{
private:
    bool recolectado = false;
    TipoRecolectable tipo;
    int puntos; // pueden funciar como puntos, puntos de vida o cantidad de munciones segun el tipo

public:

    ObjectCollected(TipoRecolectable tipo);
    
    // Devuelve los puntos que entrega al jugador que lo recolecta
    int recolectar();
    bool isCollected();
};

#endif //OBJECT_COLLECTED_H
