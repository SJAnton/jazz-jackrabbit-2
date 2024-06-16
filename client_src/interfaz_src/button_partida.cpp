#include "button_partida.h"
#include "fontManager.h"

ButtonPartida::ButtonPartida(int& id) : id_partida(id), x(100), y(100*id) {}

void ButtonPartida::renderizar(){
    fontManager font = fontManager();

	std::string texto = "PARTIDA " + std::to_string(this->id_partida);

    font.renderText(texto, this->x, this->y, 0.5f);
    font.renderText("UNIRSE", this->x + 350, this->y, 0.5f);
}


void ButtonPartida::renderizarCrearPartida() {
    fontManager font = fontManager();

    int cant_letras_texto = 13;
    int texto_width = (32 * cant_letras_texto);
    int x = (ANCHO_WINDOW - texto_width) / 2;
    int y = ALTO_WINDOW - 100;

    font.renderText("CREAR PARTIDA", x, y, 0.5f);
}

bool pointInsideButton(int& x, int& y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

bool ButtonPartida::clicked(int& mouseX, int& mouseY){
	bool cliked = pointInsideButton(mouseX, mouseY, {this->x + 350, this->y, 192, 32});
	return cliked;
}

int ButtonPartida::getIdPartida() {
    return id_partida;
}
