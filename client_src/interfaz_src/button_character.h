#ifndef BUTTON_CHARACTER_H
#define BUTTON_CHARACTER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "characters.h"
#include <string>
#include "../../common_src/constantes.h"

class ButtonCharacter{
	private:
		TipoPlayer personaje;
		int x;
		int y;
		
		int width;
		int height;

	public:
		ButtonCharacter(const TipoPlayer&, int x, int y);

		bool clicked(int& x, int& y);
		TipoPlayer getTipoPlayer();
};



#endif