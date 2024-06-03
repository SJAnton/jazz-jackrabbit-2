#include "game_mundo.h"
#include "game_terreno.h"
#include <chrono>
#include <thread>
#include <iostream>

Terreno crearTerreno() {
    Terreno terreno(6, 10);
    terreno.setFila(0, PARED);
    terreno.setFila(5, PARED);
    terreno.setColumna(0, PARED);
    terreno.setColumna(9, PARED);
    for (int i=1; i < 5; i++) {
        terreno.setValor(3, i, PARED);
    }
    return terreno;
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Terreno terreno = crearTerreno();

    GameMundo gameMundo(std::move(terreno));

    ObjectPlayer player (1);
    gameMundo.addPlayer(std::move(player), Coordenada(31, 32));
    ObjectCollected moneda(TipoRecolectable::Moneda);
    gameMundo.addItem(std::move(moneda), Coordenada(50, 40));

    //gameMundo.printCasilleros();
    int i = 0;
     while (true) {
        gameMundo.MoverPlayer(1, Right);
        gameMundo.update();

        gameMundo.printCasilleros2();
        
        // Sleep 
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
                clearConsole();

        i++;
    }
    return 0;
}
