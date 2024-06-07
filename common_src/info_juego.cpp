#include "info_juego.h"

int InfoJuego::cantidadPlayers() const {
    return players.size();
}
int InfoJuego::cantEnemigos() const {
    return enemigos.size();
}
int InfoJuego::cantRecolectables() const {
    return recolectables.size();
}
int InfoJuego::cantProyectiles() const {
    return proyectiles.size();
}
void InfoJuego::addPlayer() {
    players.push_back(InfoPlayer());
}