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
    proyectil_4(PATH_PROJECTILE_4, 24, 12, 6),
    heartIcon(PATH_HEART_ICON),
    gun_1(PATH_GUN_1, 24, 24, 10),
    gun_2(PATH_GUN_2, 24, 24, 10),
    gun_3(PATH_GUN_3, 24, 24, 9),
    gun_4(PATH_GUN_4, 32, 24, 10),
    spaz_HUD(PATH_HUD_SPAZ, 40, 40, 10),
    jazz_HUD(PATH_HUD_JAZZ, 40, 40, 11),
    lori_HUD(PATH_HUD_LORI, 46, 46, 6)
{
    SpritesTileMap::init();
    SpritesPlayers::init();
    SpritesEnemies::init();

    font = fontManager();

    gun_1.setArea(48, 48);
    gun_2.setArea(48, 48);
    gun_3.setArea(48, 48);
    gun_4.setArea(64, 48);
    spaz_HUD.setArea(20, 20);
    jazz_HUD.setArea(20, 20);
    lori_HUD.setArea(23, 23);

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

void SpritesManager::inicializarBotonesCharacter() {
    int num_characters = 3;
    int separacion = 150;
    int character_width = 144, character_height = 240;

    // Calcular el espacio total requerido para todos los personajes y las separaciones entre ellos
    int total_width = (num_characters * character_width) + ((num_characters - 1) * separacion);

    int x = (ANCHO_WINDOW - total_width) / 2;
    int y = (ALTO_WINDOW - character_height) / 2;

    botones_character.emplace_back(TipoPlayer::Jazz, x, y);
    botones_character.emplace_back(TipoPlayer::Spaz, x + character_width + separacion, y);
    botones_character.emplace_back(TipoPlayer::Lori, x + (character_width +separacion) * 2, y);
}
std::list<ButtonCharacter> SpritesManager::getBotonesCharacter() {
    return botones_character;
}
void SpritesManager::renderizarBotonesCharacter(){
    int num_characters = 3;
    int separacion = 150;
    int character_width = 144, character_height = 240;

    // Calcular el espacio total requerido para todos los personajes y las separaciones entre ellos
    int total_width = (num_characters * character_width) + ((num_characters - 1) * separacion);

    int x = (ANCHO_WINDOW - total_width) / 2;
    int y = (ALTO_WINDOW - character_height) / 2;

    // Renderizar los personajes en las posiciones calculadas
    character_jazz.renderizarEn(x, y);
    character_spaz.renderizarEn(x + character_width + separacion, y);
    character_lori.renderizarEn(x + 2 * (character_width + separacion), y);
}


void SpritesManager::renderizarPosicionesFinales(const std::vector<InfoTabla> &ranking_players){
    int tabla_x = ANCHO_WINDOW * 0.5;
    int tabla_y = ALTO_WINDOW * 0.4;
    int separacion = 40;

    font.renderText("TABLA DE POSICIONES", tabla_x, tabla_y, 0.5f);

    for (size_t i = 0; i < ranking_players.size(); i++) {
        std::string playerData = std::to_string(i + 1);
        playerData += ".PLAYER" + std::to_string(ranking_players[i].id) + " PTS:" + std::to_string(ranking_players[i].puntos);
        font.renderText(playerData, tabla_x, tabla_y + separacion, 0.5f);
        separacion += 40;
    }
}

//JUEGO

void SpritesManager::renderizarPlayer(int id) {
    SpritePlayer& player = getPlayer(id);
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

void SpritesManager::setMapa(const TileMap &mapa) {
    spritesTileMap.setTileMap(mapa);
}

void SpritesManager::renderizarItemEn(const TipoRecolectable &tipo, int x, int y) {
    if (tipo == TipoRecolectable::Moneda)
        moneda.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Diamante)
        gema.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Zanahoria)
        zanahoria.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Municion1)
        municion_1.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Municion2)
        municion_2.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Municion3)
        municion_3.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Municion4)
        municion_4.renderizarEn(x, y);
    else if (tipo == TipoRecolectable::Municion)
        municion_1.renderizarEn(x, y);
    else
        throw std::runtime_error("Item no encontrado");
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
                proyectil_2.renderizarInvertidoEn(x, y);
            else
            proyectil_2.renderizarEn(x, y);
            break;
        case Tipo_3:
            if (dir == Left)
                proyectil_3.renderizarInvertidoEn(x, y);
            else
            proyectil_3.renderizarEn(x, y);
            break;
        case Tipo_4:
            if (dir == Left)
                proyectil_4.renderizarInvertidoEn(x, y);
            else
            proyectil_4.renderizarEn(x, y);
            break;
        default:
            throw std::runtime_error("Proyectil no encontrado");
    }
}

void SpritesManager::renderizarVidas(int& vidas){
    int corazones_x = ANCHO_WINDOW * 0.94;
    int corazones_y = ALTO_WINDOW * 0.05;
    int separacion = 0;
    for (int i = 0; i < vidas; ++i)
    {
        heartIcon.renderizarEn(corazones_x + separacion, corazones_y);
        separacion -= 15;
    }
}

void SpritesManager::renderizarMunicionArma(const TipoArma &tipo, int cantMunicion){
    int municion_x = ANCHO_WINDOW * 0.8;
    int municion_y = ALTO_WINDOW * 0.84;

    //int separacion = 0;
    std::string municion;
    if(tipo == Tipo_1){
        gun_1.renderizarEn(municion_x, municion_y);
        municion += "X .";        // municoines infiintas.
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

    font.renderText(municion, municion_x + 45, municion_y, 0.7f, -20);
}

void SpritesManager::renderizarTiempo(int tiempo){
    int tabla_x = ANCHO_WINDOW / 2;
    int tabla_y = ALTO_WINDOW * 0.05;
    
    font.renderText(std::to_string(tiempo), tabla_x, tabla_y, 0.4f, -1);
}

void SpritesManager::renderizarTablaPosiciones(const std::vector<InfoTabla> &ranking_players){
    int tabla_x = ANCHO_WINDOW * 0.02;
    int tabla_y = ALTO_WINDOW * 0.05;
    int separacion = 20;
    font.renderText("RANKING", tabla_x, tabla_y, 0.23f, -4);
    
    for (size_t i = 0; i < ranking_players.size(); i++) {
            if (ranking_players[i].tipoPlayer == Lori)
                lori_HUD.renderizarEn(tabla_x, tabla_y + separacion-5);
            else if (ranking_players[i].tipoPlayer == Spaz)
                spaz_HUD.renderizarEn(tabla_x, tabla_y + separacion-5);
            else 
                jazz_HUD.renderizarEn(tabla_x, tabla_y + separacion-5);

        std::string playerData = std::to_string(i + 1);
        playerData += ".PLAYER" + std::to_string(ranking_players[i].id) + " PTS:" + std::to_string(ranking_players[i].puntos);
        font.renderText(playerData, tabla_x+40, tabla_y + separacion, 0.23f, -4);
        separacion += 20;
    }
    //lori_HUD.nextFrame();
    //spaz_HUD.nextFrame(); //No anda
    //jazz_HUD.nextFrame();
}


void SpritesManager::updateItems() {
    moneda.nextFrame();
    gema.nextFrame();
    zanahoria.nextFrame();
}

void SpritesManager::updatePlayer(int id, const EstadosPlayer &estado, const Position &pos, const Direcciones &dir) {
    SpritePlayer& player = getPlayer(id);
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

void SpritesManager::addPlayer(int id, const TipoPlayer &tipo) {
    players.emplace_back(id, tipo);
}

void SpritesManager::addEnemy(const TipoEnemy &tipo) {
    enemies.emplace_back(tipo);
}


//metodos privados:

SpritePlayer& SpritesManager::getPlayer(int id) {
    for (auto& player : players) {
        if (player.getId() == id) {
            return player;
        }
    }
    throw std::out_of_range("Player no existe en spritesManager");
}

SpriteEnemy& SpritesManager::getEnemy(unsigned int n) {
    if (n >= enemies.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto enemy = std::next(enemies.begin(), n);
    return *enemy;
}
