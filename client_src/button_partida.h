#ifndef BUTTON_PARTIDA_H
#define BUTTON_PARTIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "characters.h"

class ButtonPartida{
	private:
		int id_partida;
		int x;
		int y;
	public:
		ButtonPartida(int&);
		void renderizar(SDL_Renderer*, SDL_Texture*, Characters&);
		bool clicked(int&, int&);
};



#endif