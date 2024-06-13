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
    case Jazz: setEstadoJazz(estado_);
        break;
    case Spaz: setEstadoSpaz(estado_);
        break;
    case Lori: setEstadoLori(estado_);
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
    case EstadosPlayer::Falling : spriteSheet = SpritesPlayers::Spaz_jump; // Cambiar
        break;
    case EstadosPlayer::Shooting : spriteSheet = SpritesPlayers::Spaz_shoot;
        break;
    case EstadosPlayer::SpecialAttack : spriteSheet = SpritesPlayers::Spaz_specialAtack;
        break;
    case EstadosPlayer::IntoxicatedIdle : spriteSheet = SpritesPlayers::Spaz_intoxicatedIdle;
        break;
    case EstadosPlayer::IntoxicatedWalk : spriteSheet = SpritesPlayers::Spaz_walk;
        break;
    case EstadosPlayer::Damaged : spriteSheet = SpritesPlayers::Spaz_damaged;
        break;
    case EstadosPlayer::Dying : spriteSheet = SpritesPlayers::Spaz_death; //cambiar
        break;
    case EstadosPlayer::Dead : spriteSheet = SpritesPlayers::Spaz_death;
        break;
    case EstadosPlayer::Reviving : spriteSheet = SpritesPlayers::Spaz_idle;
        break;
    default:
        break;
    }
}

void SpritePlayer::setEstadoJazz(const EstadosPlayer &estado_) {
    switch (estado_)
    {
    case EstadosPlayer::Inactive : spriteSheet = SpritesPlayers::Jazz_idle;
        break;
    case EstadosPlayer::Walking : spriteSheet = SpritesPlayers::Jazz_walk;
        break;
    case EstadosPlayer::Running : spriteSheet = SpritesPlayers::Jazz_run;
        break;
    case EstadosPlayer::Jumping : spriteSheet = SpritesPlayers::Jazz_jump;
        break;
    case EstadosPlayer::Falling : spriteSheet = SpritesPlayers::Jazz_fall;
        break;
    case EstadosPlayer::Shooting : spriteSheet = SpritesPlayers::Jazz_shoot;
        break;
    case EstadosPlayer::SpecialAttack : spriteSheet = SpritesPlayers::Jazz_specialAtack;
        break;
    case EstadosPlayer::IntoxicatedIdle : spriteSheet = SpritesPlayers::Jazz_intoxicatedIdle;
        break;
    case EstadosPlayer::IntoxicatedWalk : spriteSheet = SpritesPlayers::Jazz_walk;
        break;
    case EstadosPlayer::Damaged : spriteSheet = SpritesPlayers::Jazz_damaged;
        break;
    case EstadosPlayer::Dying : spriteSheet = SpritesPlayers::Jazz_death; //cambiar
        break;
    case EstadosPlayer::Dead : spriteSheet = SpritesPlayers::Jazz_death;
        break;
    case EstadosPlayer::Reviving : spriteSheet = SpritesPlayers::Jazz_idle;
        break;
    default:
        break;
    }
}

void SpritePlayer::setEstadoLori(const EstadosPlayer &estado_) {
     switch (estado_)
    {
    case EstadosPlayer::Inactive : spriteSheet = SpritesPlayers::Lori_idle;
        break;
    case EstadosPlayer::Walking : spriteSheet = SpritesPlayers::Lori_walk;
        break;
    case EstadosPlayer::Running : spriteSheet = SpritesPlayers::Lori_run;
        break;
    case EstadosPlayer::Jumping : spriteSheet = SpritesPlayers::Lori_jump;
        break;
    case EstadosPlayer::Falling : spriteSheet = SpritesPlayers::Lori_fall;
        break;
    case EstadosPlayer::Shooting : spriteSheet = SpritesPlayers::Lori_shoot;
        break;
    case EstadosPlayer::SpecialAttack : spriteSheet = SpritesPlayers::Lori_specialAtack;
        break;
    case EstadosPlayer::IntoxicatedIdle : spriteSheet = SpritesPlayers::Lori_intoxicatedIdle;
        break;
    case EstadosPlayer::IntoxicatedWalk : spriteSheet = SpritesPlayers::Lori_walk;
        break;
    case EstadosPlayer::Damaged : spriteSheet = SpritesPlayers::Lori_damaged;
        break;
    case EstadosPlayer::Dying : spriteSheet = SpritesPlayers::Lori_dying;
        break;
    case EstadosPlayer::Dead : spriteSheet = SpritesPlayers::Lori_death;
        break;
    case EstadosPlayer::Reviving : spriteSheet = SpritesPlayers::Lori_idle;
        break;
    default:
        break;
    }


}
