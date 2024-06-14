#ifndef GAME_CASILLERO_H
#define GAME_CASILLERO_H

#include <set>
#include <memory>
#include <algorithm>



class Casillero {
private:
    bool bloqueado; // si es true ningun objeto puede entrar
    bool vacio;
public:
    // constructor por defecto
    Casillero() : bloqueado(false), vacio(true){};
    
    void bloquear() {bloqueado = true;};

    bool estaBloqueado() {return bloqueado;};    
};

#endif //GAME_CASILLERO_H