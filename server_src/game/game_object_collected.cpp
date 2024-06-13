#include "game_object_collected.h"


ObjectCollected::ObjectCollected(TipoRecolectable _tipo) :
    GameObject(WIDTH_COLLECTED, HEIGHT_COLLECTED)
{
    type = TypeGameObject::Collected;
    this->tipo = _tipo;
    switch (tipo)
    {
    case Diamante: puntos = PTS_DIAMANTE;
        break;
    case Moneda: puntos = PTS_MONEDA;
        break;
    case Zanahoria: puntos = PTS_VIDA;
        break;
    case Municion: puntos = PTS_MUNICION;
        break;
    default:
        break;
    }
}

int ObjectCollected::recolectar() {
    recolectado = true;
    return puntos;
}

bool ObjectCollected::isCollected() {
    return recolectado;
}
InfoRecolectable ObjectCollected::getInfo() {
    return InfoRecolectable(tipo,position.x, position.y);
}

