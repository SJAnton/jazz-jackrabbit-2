#include "sprite_player.h"


SpritePlayer::SpritePlayer(TipoPlayer tipoPlayer) :
    tipo(tipoPlayer)
{
    setEstado(EstadosPlayer::Inactivo);
}

void SpritePlayer::setFlip(bool flip_) {
    flip = flip_;
}

void SpritePlayer::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void SpritePlayer::renderizarEn(int x, int y) {
    if (flip)
        spriteSheet.renderizarInvertidoEn(x, y);
    else
        spriteSheet.renderizarEn(x, y);
}

void SpritePlayer::renderizar() {
    if (flip)
        spriteSheet.renderizarInvertidoEn(position.x, position.y);
    else
        spriteSheet.renderizarEn(position.x, position.y);
}

void SpritePlayer::updateFrame() {
    it++;
    if (it % 2 == 0) {
        spriteSheet.nextFrame();
        it = 0;
    }
}

EstadosPlayer SpritePlayer::getEstado() {
    return estado;
}


void SpritePlayer::setEstado(const EstadosPlayer &estado_) {
    estado = estado_;
    switch (this->tipo)
    {
    case Jazz:
        break;
    case Spaz: setEstadoSpaz(estado_);
        break;
    case Lori:
        break;
    default:
        return;
    }
}
//metodos privados

void SpritePlayer::setEstadoSpaz(const EstadosPlayer &estado_)
{
    switch (estado_)
    {
    case Inactivo: spriteSheet = SpritesPlayers::Spaz_idle;
        break;
    case Caminando: spriteSheet = SpritesPlayers::Spaz_walk;
        break;
    case Corriendo: spriteSheet = SpritesPlayers::Spaz_run;
        break;
    case Saltando: spriteSheet = SpritesPlayers::Spaz_jump;
        break;
    case Disparando: spriteSheet = SpritesPlayers::Spaz_shoot;
        break;
    case AtaqueEspecial: spriteSheet = SpritesPlayers::Spaz_specialAtack;
        break;
    case Impactado: spriteSheet = SpritesPlayers::Spaz_damaged;
        break;
    case IntoxicadoIdle: spriteSheet = SpritesPlayers::Spaz_intoxicatedIdle;
        break;
    case IntoxicadoWalk: spriteSheet = SpritesPlayers::Spaz_walk;
        break;
    case Muriendo: spriteSheet = SpritesPlayers::Spaz_death;
        break;
    default:
        break;
    }
}

void SpritePlayer::setEstadoJazz(const EstadosPlayer &estado_) {

}

void SpritePlayer::setEstadoLori(const EstadosPlayer &estado_) {

}
