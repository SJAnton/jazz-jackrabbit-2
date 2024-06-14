#include "game_object_collected.h"
#include <stdexcept>
#include <cstdlib>  
#include <ctime>    


// Definición de los miembros estáticos
bool ObjectCollected::initialized = false;
int ObjectCollected::Pts_Diamante = 0;
int ObjectCollected::Pts_Moneda = 0;
int ObjectCollected::Pts_Municion = 0;
int ObjectCollected::Pts_Zanahoria = 0;
int ObjectCollected::Pts_Zanahoria_Podrida = 0;
float ObjectCollected::Proba_Zanahoria_Podrida = 0.0f;

void ObjectCollected::init(int pts_diamante, int pts_moneda, int pts_municion, int pts_zanahoria, int pts_zanahoria_podrida, float proba_podrida) {
    if (proba_podrida < 0.0f || proba_podrida > 1.0f) {
        throw std::invalid_argument("Probability must be between 0 and 1");
    }

    Pts_Diamante = pts_diamante;
    Pts_Moneda = pts_moneda;
    Pts_Municion = pts_municion;
    Pts_Zanahoria = pts_zanahoria;
    Pts_Zanahoria_Podrida = pts_zanahoria_podrida;
    Proba_Zanahoria_Podrida = proba_podrida;

     // Inicializar la semilla aleatoria
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    initialized = true;
}

ObjectCollected::ObjectCollected(const TipoRecolectable &_tipo) :
    GameObject(WIDTH_COLLECTED, HEIGHT_COLLECTED)
{
    type = TypeGameObject::Collected;
    this->tipo = _tipo;
    switch (tipo)
    {
    case Diamante: 
        puntos = Pts_Diamante;
        break;
    case Moneda: 
        puntos = Pts_Moneda;
        break;
    case Zanahoria: 
        // segun la proba
        if (static_cast<float>(std::rand()) / RAND_MAX < Proba_Zanahoria_Podrida)
            puntos = Pts_Zanahoria_Podrida;
        else 
            puntos = Pts_Zanahoria;
        break;
    case Municion: 
        puntos = Pts_Municion;
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

TipoRecolectable ObjectCollected::getTipoRecolectable() {
    return tipo;
}


InfoRecolectable ObjectCollected::getInfo() {
    return InfoRecolectable(tipo,position.x, position.y);
}

