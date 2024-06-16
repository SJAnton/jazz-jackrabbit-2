#ifndef BUTTON_PARTIDA_H
#define BUTTON_PARTIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "characters.h"
#include <string>
#include "../../common_src/constantes.h"

class ButtonPartida{
	private:
		int id_partida;
		int x;
		int y;
		
		int size; //El tamaño de los caracteres
		int width;
		int height;

	public:
		ButtonPartida(int& idPartida);

		void renderizar();
		void renderizarCrearPartida();
		bool clicked(int& x, int& y);
		int getIdPartida();
};



#endif