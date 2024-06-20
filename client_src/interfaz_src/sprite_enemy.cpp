#include "sprite_enemy.h"


SpriteEnemy::SpriteEnemy(TipoEnemy tipoEnemy) :
    tipo(tipoEnemy)
{
    setEstado(EstadosEnemy::Idle);
}

void SpriteEnemy::setFlip(bool flip_) {
    flip = flip_;
}
void SpriteEnemy::setFlip(const Direcciones &dir) {
    if (dir == Left) 
        flip = true;
    else 
        flip = false;
}


void SpriteEnemy::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void SpriteEnemy::renderizarEn(int x, int y) {
    if (flip)
        spriteSheet.renderizarInvertidoEn(x, y);
    else
        spriteSheet.renderizarEn(x, y);
}

void SpriteEnemy::renderizar() {
    if (flip)
        spriteSheet.renderizarInvertidoEn(position.x, position.y);
    else
        spriteSheet.renderizarEn(position.x, position.y);
}

void SpriteEnemy::updateFrame() {
    it++;
    if (it % 2 == 0) {
        spriteSheet.nextFrame();
        it = 0;
    }
}

EstadosEnemy SpriteEnemy::getEstado() {
    return estado;
}


void SpriteEnemy::setEstado(const EstadosEnemy &estado_) {
    estado = estado_;
    switch (this->tipo)
    {
    case Rat: setEstadoRat(estado_);
        break;
    case Bat: setEstadoBat(estado_);
        break;
    case Diablo: setEstadoDiablo(estado_);
        break;
    default:
        return;
    }
}

//metodos privados

void SpriteEnemy::setEstadoBat(const EstadosEnemy &estado_)
{
    switch (estado_)
    {
    case EstadosEnemy::Idle : spriteSheet = SpritesEnemies::Bat_idle;
        break;
    case EstadosEnemy::Attack : spriteSheet = SpritesEnemies::Bat_attack;
        break;
    default:
        break;
    }
}

void SpriteEnemy::setEstadoRat(const EstadosEnemy &estado_) {
    switch (estado_)
    {
    case EstadosEnemy::Idle : spriteSheet = SpritesEnemies::Rat_idle;
        break;
    case EstadosEnemy::Walk : spriteSheet = SpritesEnemies::Rat_walk;
        break;
    case EstadosEnemy::Attack : spriteSheet = SpritesEnemies::Rat_attack;
        break;
    default:
        break;
    }
}

void SpriteEnemy::setEstadoDiablo(const EstadosEnemy &estado_) {
     switch (estado_)
    {
    case EstadosEnemy::Idle : spriteSheet = SpritesEnemies::Diablo_idle;
        break;
    case EstadosEnemy::Attack : spriteSheet = SpritesEnemies::Diablo_attack;
        break;
    case EstadosEnemy::Appear : spriteSheet = SpritesEnemies::Diablo_appear;
        break;
    case EstadosEnemy::Disappear : spriteSheet = SpritesEnemies::Diablo_disappear;
        break;
    default:
        break;
    }


}
