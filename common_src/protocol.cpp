#include "protocol.h"


/* Decodificadores */

AccionesPlayer  Protocol::decodeAction(uint8_t byte) {
    switch (byte) {
        case ACTION_IDLE: return AccionesPlayer::Idle;
        case ACTION_WALK: return AccionesPlayer::Walk;
        case ACTION_RUN: return AccionesPlayer::Run;
        case ACTION_JUMP: return AccionesPlayer::Jump;
        case ACTION_SHOOT: return AccionesPlayer::Shoot;
        case ACTION_SPECIAL_ATTACK: return AccionesPlayer::SpecialAttack;
        default:
            throw std::invalid_argument("En Protocol::encodeAction()");
            return AccionesPlayer::Idle;
    }
}

Direcciones Protocol::decodeDireccion(uint8_t byte) {
    switch (byte) {
        case LEFT: return Direcciones::Left;
        case RIGHT: return Direcciones::Right;
        default:
            throw std::invalid_argument("En Protocol::decodeDireccion()");
            return Direcciones::Right;
    }
}

TipoPlayer Protocol::decodeTipoPlayer(uint8_t byte) {
	switch (byte)
	{
	case PLAYER_TYPE_JAZZ : return Jazz;
	case PLAYER_TYPE_LORI : return Lori;
	case PLAYER_TYPE_SPAZ : return Spaz;	
	default:
		throw std::invalid_argument("Protocol::decodeTipoPlayer()");
		return Spaz;
	}
}

EstadosPlayer Protocol::decodeEstadoPlayer(uint8_t byte) {
    switch (byte) {
        case STATE_IDLE: return EstadosPlayer::Inactive;
        case STATE_WALK: return EstadosPlayer::Walking;
        case STATE_RUN: return EstadosPlayer::Running;
        case STATE_JUMP: return EstadosPlayer::Jumping;
        case STATE_FALL: return EstadosPlayer::Falling;
        case STATE_SHOOT: return EstadosPlayer::Shooting;
        case STATE_SPECIAL_ATTACK: return EstadosPlayer::SpecialAttack;
        case STATE_INTOXICATED_IDLE: return EstadosPlayer::IntoxicatedIdle;
		case STATE_INTOXICATED_WALK: return EstadosPlayer::IntoxicatedWalk;
        case STATE_DAMAGED: return EstadosPlayer::Damaged;
        case STATE_DYING: return EstadosPlayer::Dying;
        case STATE_DEAD: return EstadosPlayer::Dead;
        case STATE_REVIVE: return EstadosPlayer::Reviving;
        default: 
            throw std::invalid_argument("decodeEstadoPlayer()");
            return EstadosPlayer::Inactive;
    }
}

TipoEnemy Protocol::decodeTipoEnemy(uint8_t byte) {
	switch (byte)
	{
	case ENEMY_RAT : return Rat;
	case ENEMY_BAT : return Bat;
	case ENEMY_DIABLO : return Diablo;	
	default:
		throw std::invalid_argument("Protocol::decodeTipoEnemy()");
		return Rat;
	}
}

EstadosEnemy Protocol::decodeEstadoEnemy(uint8_t byte) {
	switch (byte)
	{
	case ENEMY_STATE_IDLE: return EstadosEnemy::Idle;
	case ENEMY_STATE_MOVE: return EstadosEnemy::Move;
	case ENEMY_STATE_ATTACK: return EstadosEnemy::Attack;
	case ENEMY_STATE_DAMAGED: return EstadosEnemy::Damaged;
	case ENEMY_STATE_DEATH: return EstadosEnemy::Death;
	default:
		throw std::invalid_argument("Protocol::decodeEstadoEnemy()");
		return EstadosEnemy::Idle;
	}
}

TipoRecolectable Protocol::decodeTipoRecolectable(uint8_t byte) {
    switch (byte)
	{
	case ITEM_MONEDA: return Moneda;
	case ITEM_DIAMANTE: return Diamante;
	case ITEM_MUNCION: return Municion;
	case ITEM_ZANAHORIA: return Zanahoria;
	default:
		throw std::invalid_argument("En Protocol::decodeTipoRecolectable()");
		return Moneda;
	}
}

TipoArma Protocol::decodeTipoArma(uint8_t byte) {
    switch (byte)
    {
    case WEAPON_TYPE1: return TipoArma::Tipo_1;
    case WEAPON_TYPE2: return TipoArma::Tipo_2;
    case WEAPON_TYPE3: return TipoArma::Tipo_3;
    case WEAPON_TYPE4: return TipoArma::Tipo_4;
    default:
		throw std::invalid_argument("En Protocol::decodeTipoArma()");
        return TipoArma::Tipo_1;
    }
}


/* Codificadores */

uint8_t Protocol::encodeAccion(const AccionesPlayer &accion) {
	switch (accion) {
		case AccionesPlayer::Idle: return ACTION_IDLE;
		case AccionesPlayer::Walk: return ACTION_WALK;
		case AccionesPlayer::Run: return ACTION_RUN;
		case AccionesPlayer::Jump: return ACTION_JUMP;
		case AccionesPlayer::Shoot: return ACTION_SHOOT;
		case AccionesPlayer::SpecialAttack: return ACTION_SPECIAL_ATTACK;
        case AccionesPlayer::ChangeWeapon: return ACTION_CHANGE_WEAPON;
		default: 
		throw std::invalid_argument("ERROR. Accion invalida");
		return ACTION_IDLE;
	}
}

uint8_t Protocol::encodeDireccion(const Direcciones &direccion) {
	switch (direccion) {
		case Left: return LEFT;
		case Right: return RIGHT;
		default: 
            throw std::invalid_argument("En Protocol::encodeDireccion()");
		    return RIGHT;
	}
}

uint8_t Protocol::encodeTipoPlayer(const TipoPlayer &tipo) {
	switch (tipo)
	{
	case Jazz : return PLAYER_TYPE_JAZZ;
	case Lori : return PLAYER_TYPE_LORI;
	case Spaz : return PLAYER_TYPE_SPAZ;	
	default:
        throw std::invalid_argument("En Protocol::encodeTipoPlayer()");
		return PLAYER_TYPE_JAZZ;
	}
}

uint8_t Protocol::encodeEstadoPlayer(const EstadosPlayer &estado) {
    switch (estado) {
        case EstadosPlayer::Inactive: return STATE_IDLE;
        case EstadosPlayer::Walking: return STATE_WALK;
        case EstadosPlayer::Running: return STATE_RUN;
        case EstadosPlayer::Jumping: return STATE_JUMP;
        case EstadosPlayer::Falling: return STATE_FALL;
        case EstadosPlayer::Shooting: return STATE_SHOOT;
        case EstadosPlayer::SpecialAttack: return STATE_SPECIAL_ATTACK;
        case EstadosPlayer::IntoxicatedIdle: return STATE_INTOXICATED_IDLE;
        case EstadosPlayer::IntoxicatedWalk: return STATE_INTOXICATED_WALK;
        case EstadosPlayer::Damaged: return STATE_DAMAGED;
        case EstadosPlayer::Dying: return STATE_DYING;
        case EstadosPlayer::Dead: return STATE_DEAD;
        case EstadosPlayer::Reviving: return STATE_REVIVE;
        default: 
            throw std::invalid_argument("En Protocol::encodeEstadoPlayer()");
            return STATE_IDLE;
    }
}

uint8_t Protocol::encodeTipoEnemy(const TipoEnemy &enemigo) {
	switch (enemigo) {
        case Rat: return ENEMY_RAT;
        case Bat: return ENEMY_BAT;
        case Diablo: return ENEMY_DIABLO;	
        default:
            throw std::invalid_argument("En Protocol::encodeTipoEnemy()");
            return ENEMY_RAT;
    }
}

uint8_t Protocol::encodeEstadoEnemy(const EstadosEnemy &byte) {
	switch (byte) {
	    case EstadosEnemy::Idle: return ENEMY_STATE_IDLE;
        case EstadosEnemy::Move: return ENEMY_STATE_MOVE;
	    case EstadosEnemy::Attack: return ENEMY_STATE_ATTACK;
	    case EstadosEnemy::Damaged: return ENEMY_STATE_DAMAGED;
	    case EstadosEnemy::Death: return ENEMY_STATE_DEATH;
	    default:
            throw std::invalid_argument("En Protocol::encodeEstadoEnemy()");
            return ENEMY_STATE_IDLE;
	}
}

uint8_t Protocol::encodeTipoRecolectable(const TipoRecolectable &tipo){
    switch (tipo) {
        case Diamante: return ITEM_DIAMANTE;
        case Moneda:   return ITEM_MONEDA;
        case Zanahoria: return ITEM_ZANAHORIA;
        case Municion: return ITEM_MUNCION;
        default:
            throw std::invalid_argument("En Protocol::encodeTipoRecolectable()");
            return ITEM_DIAMANTE;
    }
}

uint8_t Protocol::encodeTipoArma(const TipoArma &tipo) {
    switch (tipo)
    {
    case TipoArma::Tipo_1 : return WEAPON_TYPE1;
    case TipoArma::Tipo_2 : return WEAPON_TYPE2;
    case TipoArma::Tipo_3 : return WEAPON_TYPE3;
    case TipoArma::Tipo_4 : return WEAPON_TYPE4;
    default:
        throw std::invalid_argument("En Protocol::encodeTipoArma()");
        return WEAPON_TYPE1;
    }
}
