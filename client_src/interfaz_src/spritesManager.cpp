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




SpritesManager::SpritesManager() :
    botonPlay(PATH_BUTTON_PLAY),
    titulo(PATH_TITULO),
    character_spaz(PATH_CHARACTER_SPAZ),
    character_jazz(PATH_CHARACTER_JAZZ),
    character_lori(PATH_CHARACTER_LORI),
    //letras(PATH_FONT),
    fondo(PATH_FONDO_2),
    piso(PATH_PISO_1),
    pisoIzq(PATH_PISO_IZQ),
    PisoDer(PATH_PISO_DER),
    pisoDiagonalIzq(PATH_PISO_DIAGONAL_1),
    pisoDiagonalDer(PATH_PISO_DIAGONAL_2),
    pisoBloque(PATH_PISO_BLOQUE_1),
    moneda(PATH_ITEM_COIN, 28, 28, 20),
    gema(PATH_ITEM_GEM, 36, 36, 8),
    zanahoria(PATH_ITEM_ZANAHORIA, 36, 36, 20),
    proyectil_0(PATH_PROJECTILE_0, 16, 8,3),
    heartIcon(PATH_HEART_ICON)
{
    SpritesPlayers::init();

    font = fontManager();
    
    //players.emplace_back(Lori);
    
}

void SpritesManager::renderizarMenu() {
    int separacion = 120;

    SpriteObject title_screen = SpriteObject("../sprites/Title_Screen (640x398).png", ANCHO_WINDOW, ALTO_WINDOW);
    title_screen.renderizar();

    int boton_width = 282, boton_height = 84;
    botonPlay.renderizarEn((ANCHO_WINDOW - boton_width) / 2, ((ALTO_WINDOW - boton_height) / 2) + separacion);

    //int titulo_width = 560, titulo_height = 224;
    //titulo.renderizarEn((ANCHO_WINDOW - titulo_width) / 2, ((ALTO_WINDOW - titulo_height) / 2) - separacion);
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
        button.renderizar();
    }
    botones_partidas.back().renderizarCrearPartida();
}


void SpritesManager::inicializarBotonesCharacter(){
    int separacion = 250;
    int character_width = 144, character_height = 240;
    int x = ((ANCHO_WINDOW / 3) - character_width) / 2;
    int y = (ALTO_WINDOW - character_height) / 2;

    botones_character.emplace_back(TipoPlayer::Jazz, x, y);
    botones_character.emplace_back(TipoPlayer::Spaz, x + separacion, y);
    botones_character.emplace_back(TipoPlayer::Lori, x + separacion * 2, y);
}

std::list<ButtonCharacter> SpritesManager::getBotonesCharacter() {
    return botones_character;
}

void SpritesManager::renderizarBotonesCharacter(){
    int separacion = 250;
    int character_width = 144, character_height = 240;
    int x = ((ANCHO_WINDOW / 3) - character_width) / 2;
    int y = (ALTO_WINDOW - character_height) / 2;

    character_jazz.renderizarEn(x, y);
    character_spaz.renderizarEn(x + separacion, y);
    character_lori.renderizarEn(x + separacion * 2, y);
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

void SpritesManager::renderizarFondo(const Position &posCamara)
{
    int size = 64;
    fondo.setArea(size, size);
    piso.setArea(size, size);
    pisoBloque.setArea(size, size);
    for (int i = -15; i < 25; i++) {
        for (int j = -15; j < 25; j++) { //HARDCODEADO
            fondo.renderizarEn(size*i - posCamara.x, size*j - posCamara.y);
        }
    }
    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 10; j++) { //HARDCODEADO
            //fondo.renderizarEn(size*i - posCamara.x, size*j - posCamara.y);
            piso.renderizarEn(size*i - posCamara.x, 4*64  - posCamara.y); //Fila 4
            pisoBloque.renderizarEn(i*size - posCamara.x, 5*64 - posCamara.y);
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

void SpritesManager::renderizarProyectilEn(const Direcciones &dir, int x, int y) {
    if (dir == Left)
        proyectil_0.renderizarInvertidoEn(x, y);
    else 
        proyectil_0.renderizarEn(x, y);
}

void SpritesManager::renderizarVidas(int& vidas){
    int corazones_x = ANCHO_WINDOW * 0.9;
    int corazones_y = ALTO_WINDOW * 0.05;
    int separacion = 0;
    for (int i = 0; i < vidas; ++i)
    {
        heartIcon.renderizarEn(corazones_x + separacion, corazones_y);
        separacion -= 30;
    }
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

void SpritesManager::updateProyectiles() {
    proyectil_0.nextFrame();
}

void SpritesManager::addPlayer(const TipoPlayer &tipo) {
    players.emplace_back(tipo);
}


//metodos privados:

SpritePlayer& SpritesManager::getPlayer(unsigned int n) {
    if (n >= players.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto player = std::next(players.begin(), n);
    return *player;
}
