#include "button_character.h"

ButtonCharacter::ButtonCharacter(const TipoPlayer& pj, int x, int y) : personaje(pj), x(x), y(y), width(144), height(240) {}

bool pointInsideCharacter(int& x, int& y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

bool ButtonCharacter::clicked(int& mouseX, int& mouseY){
	bool cliked = pointInsideCharacter(mouseX, mouseY, {this->x, this->y, width, height});
	return cliked;
}

TipoPlayer ButtonCharacter::getTipoPlayer(){
	return personaje;
}