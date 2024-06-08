#ifndef BUTTON_PARTIDA_H
#define BUTTON_PARTIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "characters.h"
#include <string>

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

		void renderizar(SDL_Renderer*, SDL_Texture*);
		void renderizarCrearPartida(SDL_Renderer* renderer, SDL_Texture* fontTexture);
		bool clicked(int& x, int& y);
		int getIdPartida();
};



#endif