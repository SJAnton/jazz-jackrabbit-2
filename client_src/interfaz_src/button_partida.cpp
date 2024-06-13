#include "button_partida.h"

ButtonPartida::ButtonPartida(int& id) : id_partida(id), x(100), y(100*id) {}

void renderTextPartida(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<char,
                SDL_Rect>& charMap, const std::string& text, int x, int y, float scale) {
    for (char c : text) {
        auto it = charMap.find(c);
        if (it != charMap.end()) { // Si se encuentra el carácter en el mapa
            SDL_Rect srcRect = it->second;
            SDL_Rect dstRect = { x, y, static_cast<int>(srcRect.w * scale), 
                                static_cast<int>(srcRect.h * scale) };
            SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
            x += dstRect.w;
        } else if (c == ' ') { // Si el carácter es un espacio
            x += static_cast<int>(64 * scale); // Avanza el ancho de un espacio
        }
    }
}

void ButtonPartida::renderizar(SDL_Renderer* renderer, SDL_Texture* fontTexture){
    Characters fontMap = Characters();

	std::string texto = "PARTIDA " + std::to_string(this->id_partida);

	renderTextPartida(renderer, fontTexture, fontMap.charMap, texto, this->x, this->y, 0.5f);
	renderTextPartida(renderer, fontTexture, fontMap.charMap, "UNIRSE", this->x + 350, this->y, 0.5f);
}

void renderText(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<char,
                SDL_Rect>& charMap, const std::string& text, int x, int y, float scale) {
    for (char c : text) {
        auto it = charMap.find(c);
        if (it != charMap.end()) { // Si se encuentra el carácter en el mapa
            SDL_Rect srcRect = it->second;
            SDL_Rect dstRect = { x, y, static_cast<int>(srcRect.w * scale), 
                                static_cast<int>(srcRect.h * scale) };
            SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
            x += dstRect.w;
        } else if (c == ' ') { // Si el carácter es un espacio
            x += static_cast<int>(64 * scale); // Avanza el ancho de un espacio
        }
    }
}

void ButtonPartida::renderizarCrearPartida(SDL_Renderer* renderer, SDL_Texture* fontTexture) {
    Characters fontMap = Characters();
    int cant_letras_texto = 13;
    int texto_width = (32 * cant_letras_texto);
    int x = (ANCHO_WINDOW - texto_width) / 2;
    int y = ALTO_WINDOW - 100;
    renderText(renderer, fontTexture, fontMap.charMap, "CREAR PARTIDA", x, y, 0.5f);  

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
