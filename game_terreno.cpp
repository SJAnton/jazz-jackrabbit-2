#include "game_terreno.h"

void Terreno::chequearRango(int fila, int col) const {
    if (fila < 0 || fila >= cant_filas) {
        std::runtime_error("Valor de fila del terreno fuera del rango");
    } else if (col < 0 || col >= cant_columnas) {
        std::runtime_error("Valor de columna del terreno fuera del rango");
    }
}

Terreno::Terreno(int filas, int columnas) : cant_filas(filas), cant_columnas(columnas) {
    inicializarTerrenoVacio();
}

Terreno::Terreno(const Terreno& other)
    : cant_filas(other.cant_filas), cant_columnas(other.cant_columnas), terreno(other.terreno) {}

Terreno::Terreno(Terreno&& other) noexcept
    : cant_filas(other.cant_filas), cant_columnas(other.cant_columnas), terreno(std::move(other.terreno)) {
    other.cant_filas = 0;
    other.cant_columnas = 0;
}

char Terreno::getValor(int fila, int col) const {
    this->chequearRango(fila, col);
    return terreno[fila][col];
}
int Terreno::getFilas() const {
    return cant_filas;
}
int Terreno::getColumnas() const {
    return cant_columnas;
}


void Terreno::setValor(int fila, int col, char valor) {
    chequearRango(fila, col);
    terreno[fila][col] = valor;
}

// Establece los valores de una fila del terreno
void Terreno::setFila(int fila, char valores[]) {
    chequearRango(fila, 0);

    for (int col = 0; col < cant_columnas; col++) {
        terreno[fila][col] = valores[col];
    }
    
}
void Terreno::setFila(int fila, char valor) {
    chequearRango(fila, 0);

    for (int col = 0; col < cant_columnas; col++) {
        terreno[fila][col] = valor;
    }
    
}

void Terreno::setColumna(int col, char valores[]) {
    chequearRango(0, col);
    for (int fila = 0; fila < cant_filas; fila++) {
        terreno[fila][col] = valores[fila];
    }
}
void Terreno::setColumna(int col, char valor) {
    if (col >= 0 && col < cant_columnas) {
        for (int fila = 0; fila < cant_filas; fila++) {
            terreno[fila][col] = valor;
        }
    } else {
        std::cerr << "Índice de columna fuera de rango." << std::endl;
    }
}


std::string Terreno::toString() {
    std::string result;
    for (int fila = 0; fila < cant_filas; fila++) {
        for (int col = 0; col < cant_columnas; col++) {
            result += " ";
            result += terreno[fila][col];
        }
        result += '\n';
    }
    return result;
}

void Terreno::inicializarTerrenoVacio() {
    terreno = std::vector<std::vector<char>>(cant_filas, std::vector<char>(cant_columnas, VACIO));
}
