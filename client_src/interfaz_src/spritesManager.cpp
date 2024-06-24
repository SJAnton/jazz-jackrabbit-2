#include "spritesManager.h"
#include "interfaz_grafica.h"
#include <iostream>


 #define PATH_PANTALLA_INICIO "../sprites/Title_Screen (640x398).png"

SpritesManager::SpritesManager() :
    botonPlay(PATH_BUTTON_PLAY),
    titulo(PATH_TITULO),
    character_spaz(PATH_CHARACTER_SPAZ),
    character_jazz(PATH_CHARACTER_JAZZ),
    character_lori(PATH_CHARACTER_LORI),
    //letras(PATH_FONT),
    spritesTileMap(TileMap::getLevel_1()),  //CAMBIAR
    moneda(PATH_ITEM_COIN, 28, 28, 20),
    gema(PATH_ITEM_GEM, 36, 36, 8),
    zanahoria(PATH_ITEM_ZANAHORIA, 36, 36, 20),
    municion_1(PATH_ITEM_MUNICION_1, 24, 24, 10),
    municion_2(PATH_ITEM_MUNICION_2, 24, 24, 9),
    municion_3(PATH_ITEM_MUNICION_3, 24, 24, 10),
    municion_4(PATH_ITEM_MUNICION_4, 24, 24, 10),
    proyectil_0(PATH_PROJECTILE_0, 16, 8,3),
    proyectil_1(PATH_PROJECTILE_1, 24, 12, 6),
    proyectil_2(PATH_PROJECTILE_2, 24, 12, 6),
    proyectil_3(PATH_PROJECTILE_3, 24, 12, 6),
    heartIcon(PATH_HEART_ICON),
    gun_1(PATH_GUN_1, 24, 24, 10),
    gun_2(PATH_GUN_2, 24, 24, 10),
    gun_3(PATH_GUN_3, 24, 24, 9),
    gun_4(PATH_GUN_4, 32, 24, 10)

    //spazGun(PATH_SPAZ_GUN, 24, 24, 10),
    //jazzGun(PATH_JAZZ_GUN, 24, 24, 10),
    //loriGun(PATH_LORI_GUN, 16, 16, 5)
{
    SpritesTileMap::init();
    SpritesPlayers::init();
    SpritesEnemies::init();

    font = fontManager();
}

void SpritesManager::renderizarMenu() {
    int separacion = 120;

    SpriteObject title_screen = SpriteObject(PATH_PANTALLA_INICIO, ANCHO_WINDOW, ALTO_WINDOW);
    title_screen.renderizar();

    int boton_width = 282, boton_height = 84;
    botonPlay.renderizarEn((ANCHO_WINDOW - boton_width) / 2, ((ALTO_WINDOW - boton_height) / 2) + separacion);

    //int titulo_width = 560, titulo_height = 224;
    //titulo.renderizarEn((ANCHO_WINDOW - titulo_width) / 2, ((ALTO_WINDOW - titulo_height) / 2) - separacion);
}

void SpritesManager::inicializarBotonesPartidas(const std::vector<int> &id_partidas) {
    //int cantidad = id_partidas.size();
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
/*
void SpritesManager::renderizarPlayerEn(unsigned int n, int x, int y)
{
    SpritePlayer& player = getPlayer(n);
    if (playerInvertido)
        player.setFlip(true);
    player.renderizarEn(x, y);

}
*/

void SpritesManager::renderizarPlayer(unsigned int n) {
    SpritePlayer& player = getPlayer(n);
    player.renderizar();
}
void SpritesManager::renderizarEnemigo(unsigned int n) {
    SpriteEnemy& enemy = getEnemy(n);
    if (enemy.getEstado() == EstadosEnemy::Death) {
        return;
    }
    enemy.renderizar();
}

void SpritesManager::renderizarTerreno(const Position &posCamara) {
   spritesTileMap.renderizar(posCamara);
}

void SpritesManager::renderizarItemEn(const TipoRecolectable &tipo, int x, int y) {
    if (tipo == TipoRecolectable::Moneda)
        moneda.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Diamante)
        gema.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Zanahoria)
        zanahoria.renderizarEn(x, y);
}

void SpritesManager::renderizarProyectilEn(const Direcciones &dir, TipoArma &tipo ,int x, int y) {
    switch (tipo) {
        case Tipo_1:
            if (dir == Left)
                proyectil_0.renderizarInvertidoEn(x, y);
            else 
                proyectil_0.renderizarEn(x, y);
            break;
        case Tipo_2:
            if (dir == Left)
                proyectil_1.renderizarInvertidoEn(x, y);
            else
            proyectil_1.renderizarEn(x, y);
            break;
        case Tipo_3:
            if (dir == Left)
                proyectil_2.renderizarInvertidoEn(x, y);
            else
            proyectil_2.renderizarEn(x, y);
            break;
        case Tipo_4:
            if (dir == Left)
                proyectil_3.renderizarInvertidoEn(x, y);
            else
            proyectil_3.renderizarEn(x, y);
            break;
        default:
            throw std::runtime_error("Proyectil no encontrado");
    }
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

void SpritesManager::renderizarMunicionArma(const TipoArma &tipo, int cantMunicion){
    int municion_x = ANCHO_WINDOW * 0.8;
    int municion_y = ALTO_WINDOW * 0.9;

    //int separacion = 0;
    std::string municion;
    if(tipo == Tipo_1){
        gun_1.renderizarEn(municion_x, municion_y);
        municion += "X.";        // municoines infiintas.
    }
    else if(tipo == Tipo_2){
        gun_2.renderizarEn(municion_x, municion_y);
    }
    else if(tipo == Tipo_3){
        gun_3.renderizarEn(municion_x, municion_y);
    }
    else if (tipo == Tipo_4) {
        gun_4.renderizarEn(municion_x, municion_y);
    }
    
    if(tipo != Tipo_1){ 
        municion += "X" + std::to_string(cantMunicion);
    }

    font.renderText(municion, municion_x + 30, municion_y, 0.4f);
}


void SpritesManager::updateItems() {
    moneda.nextFrame();
    gema.nextFrame();
    zanahoria.nextFrame();
}

/*
void SpritesManager::flipPlayer(unsigned int n, bool invertirSprite) 
{
    SpritePlayer& player = getPlayer(n);
    player.setFlip(invertirSprite);
}
*/
void SpritesManager::updatePlayer(unsigned int n, const EstadosPlayer &estado, const Position &pos, const Direcciones &dir) {
    SpritePlayer& player = getPlayer(n);
    player.setPosition(pos.x, pos.y);
    player.setFlip(dir);
    if (player.getEstado() != estado) { // si cambió de estado
        player.setEstado(estado);
    }
    else {
        player.updateFrame();
    }
}

void SpritesManager::updateEnemy(unsigned int n, const EstadosEnemy &estado, const Position &pos, const Direcciones &dir) {
    SpriteEnemy& enemy = getEnemy(n);
    enemy.setPosition(pos.x, pos.y);
    enemy.setFlip(dir);
    if (enemy.getEstado() != estado) { // si cambió de estado
        enemy.setEstado(estado);
    }
    else { // si mantuvo el estado
        enemy.updateFrame();
    }
}

void SpritesManager::updateProyectiles() {
    proyectil_0.nextFrame();
}

void SpritesManager::addPlayer(const TipoPlayer &tipo) {
    players.emplace_back(tipo);
}

void SpritesManager::addEnemy(const TipoEnemy &tipo) {
    enemies.emplace_back(tipo);
}


//metodos privados:

SpritePlayer& SpritesManager::getPlayer(unsigned int n) {
    if (n >= players.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto player = std::next(players.begin(), n);
    return *player;
}

SpriteEnemy& SpritesManager::getEnemy(unsigned int n) {
    if (n >= enemies.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto enemy = std::next(enemies.begin(), n);
    return *enemy;
}
