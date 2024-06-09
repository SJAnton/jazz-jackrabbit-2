#include "spritesManager.h"
#include "interfaz_grafica.h"
#include <iostream>

 // Definirlas en 'sprites_paths.h'
//TERRENO
#define PATH_PISO_1 "../sprites/Terreno/tile012.png"
#define PATH_PISO_2 "../sprites/Terreno/tile013.png"
#define PATH_PISO_DIAGONAL_1 "../sprites/Terreno/tile011.png"
#define PATH_PISO_DIAGONAL_2 "../sprites/Terreno/tile006.png"
#define PATH_PISO_IZQ "../sprites/Terreno/tile000.png"
#define PATH_PISO_DER "../sprites/Terreno/tile001.png"
#define PATH_PISO_BLOQUE_1 "../sprites/Terreno/tile008.png"


#define PATH_FONDO_2 "../sprites/Terreno/tile002.png"

#define PATH_BUTTON_PLAY "../sprites/boton_play.png"
#define PATH_TITULO "../sprites/titulo.png"
#define PATH_FONT "../sprites/font.png"

SpritesManager::SpritesManager() :
    botonPlay(PATH_BUTTON_PLAY),
    titulo(PATH_TITULO),
    //letras(PATH_FONT),
    fondo(PATH_FONDO_2),
    piso(PATH_PISO_1),
    pisoIzq(PATH_PISO_IZQ),
    PisoDer(PATH_PISO_DER),
    pisoDiagonalIzq(PATH_PISO_DIAGONAL_1),
    pisoDiagonalDer(PATH_PISO_DIAGONAL_2),
    pisoBloque(PATH_PISO_BLOQUE_1),
    moneda(PATH_ITEM_COIN, 28, 28, 20),
    gema(PATH_ITEM_GEM, 56, 56, 8),
    zanahoria(PATH_ITEM_ZANAHORIA, 36, 36, 10)
{
    botonPlay.setPosition(234, 258);
    titulo.setPosition(95, 28);

    SpritesPlayers::init();

    //Temporal. Armar mejor la clase ButtonPartida
    SDL_Surface* surface = IMG_Load(PATH_FONT);
    fontTexture = SDL_CreateTextureFromSurface(InterfazGrafica::renderer, surface);
    SDL_FreeSurface(surface);

    
    players.emplace_back(Spaz);
    players.emplace_back(Spaz);
    players.emplace_back(Spaz);
}

void SpritesManager::renderizarMenu() {
    botonPlay.renderizar();
    titulo.renderizar();
}

void SpritesManager::inicializarBotonesPartidas(const std::vector<int> &id_partidas) {
    int cantidad = id_partidas.size();
    for (int id : id_partidas) {
        botones_partidas.emplace_back(id); 
        //Estaria bueno que el tamaño de los botones  y letras dependa de la cantidad de partidas 
        //porque no van a entrar en la pantalla si hay muchas
    }
}

std::list<ButtonPartida> SpritesManager::getBotonesPartidas() {
    return botones_partidas;
}

void SpritesManager::renderizarBotonesPartidas() {
    for (auto button : botones_partidas) {
        button.renderizar(InterfazGrafica::renderer, fontTexture);
    }
    botones_partidas.back().renderizarCrearPartida(InterfazGrafica::renderer, fontTexture);
}


//JUEGO
void SpritesManager::renderizarPlayerEn(unsigned int n, int x, int y)
{
    SpritePlayer& player = getPlayer(n);
    if (playerInvertido)
        player.setFlip(true);
    player.renderizarEn(x, y);

}

void SpritesManager::renderizarPlayer(unsigned int n) {
    SpritePlayer& player = getPlayer(n);
    player.renderizar();
}

void SpritesManager::renderizarFondo()
{
    int size = 64;
    fondo.setArea(size, size);
    piso.setArea(size, size);
    pisoBloque.setArea(size, size);

    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 10; j++) {
            fondo.renderizarEn(size*i, size*j);
            piso.renderizarEn(size*i, 300);
            pisoBloque.renderizarEn(i*size, 364);
        }
    }
}

void SpritesManager::renderizarItemEn(const TipoRecolectable &tipo, int x, int y) {
    if (tipo == TipoRecolectable::Moneda)
        moneda.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Diamante)
        gema.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Zanahoria)
        zanahoria.renderizarEn(x, y);
}
void SpritesManager::updateItems() {
    moneda.nextFrame();
    gema.nextFrame();
    zanahoria.nextFrame();
}
void SpritesManager::flipPlayer(unsigned int n, bool invertirSprite) 
{
    SpritePlayer& player = getPlayer(n);
    player.setFlip(invertirSprite);
}



void SpritesManager::updatePlayer(unsigned int n, const EstadosPlayer &estado, const Position &pos) {
    SpritePlayer& player = getPlayer(n);
    player.setPosition(pos.x, pos.y);
    if (player.getEstado() != estado) { // si cambió de estado
        player.setEstado(estado);
    }
    else {
        player.updateFrame();
    }
}

//metodos privados:

SpritePlayer& SpritesManager::getPlayer(unsigned int n) {
    if (n >= players.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto player = std::next(players.begin(), n);
    return *player;
}
