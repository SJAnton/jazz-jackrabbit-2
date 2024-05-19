#include "spritesManager.h"

//las defino acá porque nadie mas necesita esta informacion

//player Spaz
#define PATH_SPAZ_IDLE "../sprites/Players/Spaz/Idle (56x56)x06.png"
#define PATH_SPAZ_WALK "../sprites/Players/Spaz/Walk (56x56)x08.png"
#define PATH_SPAZ_RUN 
#define PATH_SPAZ_JUMP "../sprites/Players/Spaz/Jump (56x56)x12.png"
#define PATH_SPAZ_SHOOT "../sprites/Players/Spaz/Shoot (56x56)x06.png"
#define PATH_SPAZ_SPECIAL "../sprites/Players/Spaz/Special Attack (56x56)x12.png"
#define PATH_SPAZ_DEATH "../sprites/Players/Spaz/Death (96x96)x26.png"

//TERRENO
#define PATH_PISO_1 "../sprites/Terreno/tile012.png"
#define PATH_PISO_2 "../sprites/Terreno/tile013.png"
#define PATH_PISO_DIAGONAL_1 "../sprites/Terreno/tile011.png"
#define PATH_PISO_DIAGONAL_2 "../sprites/Terreno/tile006.png"
#define PATH_PISO_IZQ "../sprites/Terreno/tile000.png"
#define PATH_PISO_DER "../sprites/Terreno/tile001.png"
#define PATH_PISO_BLOQUE_1 "../sprites/Terreno/tile008.png"


#define PATH_FONDO_2 "../sprites/Terreno/tile002.png"

std::string s = "../sprites/Players/Spaz/Idle (56x56)x06.png";

SpritesManager::SpritesManager() :
    fondo(PATH_FONDO_2),
    piso(PATH_PISO_1),
    pisoIzq(PATH_PISO_IZQ),
    PisoDer(PATH_PISO_DER),
    pisoDiagonalIzq(PATH_PISO_DIAGONAL_1),
    pisoDiagonalDer(PATH_PISO_DIAGONAL_2),
    pisoBloque(PATH_PISO_BLOQUE_1),

    playerSpaz_idle(PATH_SPAZ_IDLE, 56, 56, 6, Spaz),
    playerSpaz_walk(PATH_SPAZ_WALK, 56, 56, 8, Spaz),
    playerSpaz_jump(PATH_SPAZ_JUMP, 56, 56, 12, Spaz),
    playerSpaz_shoot(PATH_SPAZ_SHOOT, 56, 56, 6, Spaz),
    playerSpaz_specialAtack(PATH_SPAZ_SPECIAL , 56, 56, 12, Spaz),
    playerSpaz_death(PATH_SPAZ_DEATH, 96, 96, 26, Spaz)
{
    players.push_back(playerSpaz_idle);
    players.push_back(playerSpaz_idle);
    players.push_back(playerSpaz_idle);
    estadosPlayers.push_back(EstadosPlayer::Inactivo);
    estadosPlayers.push_back(EstadosPlayer::Inactivo);
    estadosPlayers.push_back(EstadosPlayer::Inactivo);

}

void SpritesManager::nextFramePlayer(unsigned int n)
{
    SpriteSheetPlayer& player = getPlayer(n);
    player.nextFrame();
}
void SpritesManager::renderizarPlayerEn(unsigned int n, int x, int y)
{
    SpriteSheetPlayer& player = getPlayer(n);
    if (playerInvertido)
        player.renderizarInvertidoEn(x, y);
    else
        player.renderizarEn(x, y);
}

EstadosPlayer SpritesManager::getEstadoPlayer(unsigned int n)
{
    if (n > estadosPlayers.size())
        throw std::runtime_error("numero de player inexistente. SpritesManager::getEstadoPlayer()");
    return estadosPlayers[n];
}

void SpritesManager::setEstadoPlayer(unsigned int n, EstadosPlayer estado)
{
    SpriteSheetPlayer& player = getPlayer(n);

    if (player.getTipo() == Spaz) {
        setPlayerSpaz(player, estado);
    }
    else if (player.getTipo() == Jazz){
        setPlayerSpaz(player, estado);//jazz
    }
    else {
        setPlayerSpaz(player, estado);//lori
    }
    estadosPlayers[n] = estado;
}

void SpritesManager::renderizarFondo()
{
    fondo.setArea(64, 64);
    piso.setArea(64, 64);
    pisoBloque.setArea(64, 64);

    for (size_t i = 0; i < 15; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            fondo.renderizarEn(64*i, 64*j);
            piso.renderizarEn(64*i, 300);
            pisoBloque.renderizarEn(i*64, 364);
        }
    }
}

void SpritesManager::flipPlayer(unsigned int n, bool invertirSprite) 
{
    playerInvertido = invertirSprite;

}
//metodos privados:

SpriteSheetPlayer& SpritesManager::getPlayer(unsigned int n) {
    if (n >= players.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto player = std::next(players.begin(), n);
    return *player;
}

void SpritesManager::setPlayerSpaz(SpriteSheet &player, EstadosPlayer estado)
{
    if (estado == Inactivo)
        player = playerSpaz_idle;
    else if (estado == Caminando) {
        player = playerSpaz_walk;
    }
    else if (estado == Saltando)
        player = playerSpaz_jump;
    else if (estado == Disparando)
        player = playerSpaz_shoot;
    else if (estado == AtaqueEspecial)
        player = playerSpaz_specialAtack;
    else if (estado == Muriendo)
        player = playerSpaz_death;
}
