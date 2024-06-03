#ifndef TERRENO_H
#define TERRENO_H

#include <vector>
#include <iostream>
#include <stdexcept>

const char VACIO = ' ';
const char PARED = 'X';
const char PLAYER1 = 'A';
const char PLAYER2 = 'B';
const char MONEDA = 'M';

/**
 * Un bloque de terreno equivaldrá a 64x64 px de la interfaz del cliente.
 * Es una simplificacion del GameMundo. Se usa para poder crear terrenos mas facil.
*/
class Terreno {
private:
    int cant_filas;
    int cant_columnas;
    std::vector<std::vector<char>> terreno;

private:
    void inicializarTerrenoVacio();
    //void inicializarTerreno1(); usar algun terreno predeterminado (hardcodeado en algun terrenos.h)
    //void inicializarTerreno2();

    void chequearRango(int fila, int col) const ;
public:

    Terreno(int filas, int columnas);

    Terreno(const Terreno& other); // Constructor de copia
    Terreno(Terreno&& other) noexcept; // Constructor de movimiento
    Terreno& operator=(const Terreno& other); // Asignación de copia
    Terreno& operator=(Terreno&& other) noexcept; // Asignación de movimiento
    // Función para obtener un elemento del terreno
    char getValor(int fila, int col) const;

    int getFilas() const;
    int getColumnas() const;

    // Función para modificar un elemento del terreno
    void setValor(int fila, int col, char valor);

    void setFila(int fila, char valores[]);
    void setFila(int col, char valor);

    void setColumna(int col, char valores[]);
    void setColumna(int col, char valor);

    std::string toString();
};

#endif // TERRENO_H
