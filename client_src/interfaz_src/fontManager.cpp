#include "fontManager.h"
#include "interfaz_grafica.h"

fontManager::fontManager(){
	renderer = InterfazGrafica::renderer;

	Characters fontMap = Characters();
	charMap = fontMap.charMap;

	SDL_Surface* surface = IMG_Load(PATH_FONT);
    fontTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void fontManager::renderText(const std::string& text, int x, int y, float scale) {
    for (char c : text) {
        auto it = charMap.find(c);
        if (it != charMap.end()) { // Si se encuentra el carácter en el mapa
            SDL_Rect srcRect = it->second;
            SDL_Rect dstRect = { x, y, static_cast<int>(srcRect.w * scale), 
                                static_cast<int>(srcRect.h * scale) };
            SDL_RenderCopy(renderer, fontTexture, &srcRect, &dstRect);
            x += dstRect.w;
        } else if (c == ' ') { // Si el carácter es un espacio
            x += static_cast<int>(64 * scale); // Avanza el ancho de un espacio
        }
    }
}