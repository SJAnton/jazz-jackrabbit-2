#ifndef GAME_COORDENADA_H
#define GAME_COORDENADA_H

#define MULTIPLCADOR_CASILLERO 32


/**
 * En la escala del terreno (del tilemap)
*/
class CoordenadaBloque
{
public:
    unsigned int x;
    unsigned int y;

    CoordenadaBloque() {};
    explicit CoordenadaBloque(unsigned int x, unsigned int y) : x(x), y(y) {};
};


/**
 * En la escala del juego 
*/
class Coordenada
{
public:
    unsigned int x;
    unsigned int y;

    Coordenada() {};
    explicit Coordenada(unsigned int x, unsigned int y) : x(x), y(y) {};
  
    CoordenadaBloque toBloque() const{
        return CoordenadaBloque(x/MULTIPLCADOR_CASILLERO, y/MULTIPLCADOR_CASILLERO);
    };
};

#endif //GAME_COORDENADA_H