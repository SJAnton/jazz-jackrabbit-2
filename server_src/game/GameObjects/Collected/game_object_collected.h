#ifndef OBJECT_COLLECTED_H
#define OBJECT_COLLECTED_H

#include "../game_object.h"

#include "../../../../common_src/constantes.h"
#include "../../../../common_src/info_juego.h"

#define PTS_DIAMANTE 20
#define PTS_MONEDA 10
#define PTS_VIDA 1
#define PTS_MUNICION 3

#define WIDTH_COLLECTED 24
#define HEIGHT_COLLECTED 24

// No hace falta polimorfismo porque en escencia todas hacen lo mismo 
// (devolver un numero entero cuando son recolectadas)
class ObjectCollected : public GameObject {
private:
    static bool initialized;
    static int Pts_Diamante;
    static int Pts_Moneda;
    static int Pts_Municion;
    static int Pts_Zanahoria;
    static int Pts_Zanahoria_Podrida;
    static float Proba_Zanahoria_Podrida;

    bool recolectado = false;
    TipoRecolectable tipo;
    int puntos; // pueden funcionar como puntos, puntos de vida o cantidad de munciones segun el tipo

public:
    static void init(int pts_diamante, int pts_moneda, int pts_municion, int pts_zanahoria, int pts_zanahoria_podrida, int proba_podrida);
    ObjectCollected(const TipoRecolectable &tipo);

    // Devuelve los puntos que entrega al jugador que lo recolecta
    int recolectar();
    bool isCollected();

    TipoRecolectable getTipoRecolectable();

    InfoRecolectable getInfo();
};

#endif //OBJECT_COLLECTED_H