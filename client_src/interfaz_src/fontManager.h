#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "characters.h"
#include <string>
#include "../../common_src/constantes.h"

class fontManager{
	private:
		std::unordered_map<char, SDL_Rect> charMap;
		SDL_Texture* fontTexture;
		SDL_Renderer* renderer;
	public:
		fontManager();
		void renderText(const std::string& text, int x, int y, float scale);

};


#endif
