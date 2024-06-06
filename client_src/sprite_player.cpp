#include "sprite_player.h"


SpritePlayer::SpritePlayer(TipoPlayer tipoPlayer) :
    tipo(tipoPlayer)
{
    setEstado(EstadosPlayer::Inactive);
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
    case EstadosPlayer::Inactive : spriteSheet = SpritesPlayers::Spaz_idle;
        break;
    case EstadosPlayer::Walking : spriteSheet = SpritesPlayers::Spaz_walk;
        break;
    case EstadosPlayer::Running : spriteSheet = SpritesPlayers::Spaz_run;
        break;
    case EstadosPlayer::Jumping : spriteSheet = SpritesPlayers::Spaz_jump;
        break;
    case EstadosPlayer::Shooting : spriteSheet = SpritesPlayers::Spaz_shoot;
        break;
    case EstadosPlayer::SpecialAttack : spriteSheet = SpritesPlayers::Spaz_specialAtack;
        break;
    case EstadosPlayer::Damaged : spriteSheet = SpritesPlayers::Spaz_damaged;
        break;
    case EstadosPlayer::IntoxicatedIdle : spriteSheet = SpritesPlayers::Spaz_intoxicatedIdle;
        break;
    case EstadosPlayer::IntoxicatedWalk : spriteSheet = SpritesPlayers::Spaz_walk;
        break;
    case EstadosPlayer::Dying : spriteSheet = SpritesPlayers::Spaz_death;
        break;
    //case EstadosPlayer::Reviving;
    //case EstadosPlayer::Death;

    default:
        break;
    }
}

void SpritePlayer::setEstadoJazz(const EstadosPlayer &estado_) {

}

void SpritePlayer::setEstadoLori(const EstadosPlayer &estado_) {

}
