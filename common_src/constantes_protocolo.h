#ifndef CONSTANTES_PROTOCOLO_H
#define CONSTANTES_PROTOCOLO_H

#define SIZE_CLIENT_MSG 3
#define SIZE_CLIENT_MSG_INIT 2


//Comandos o acciones que puede enviar un Cliente
#define ACTION_IDLE 0x11
#define ACTION_WALK 0x12
#define ACTION_RUN 0x13
#define ACTION_JUMP 0x14
#define ACTION_SHOOT 0x15
#define ACTION_SPECIAL_ATTACK 0x16
#define ACTION_CHANGE_WEAPON 0x17
// La accion vendrá seguida de la direccion en el eje x
#define LEFT 0x4C // L
#define RIGHT 0x52 // R

#define PLAYER_TYPE_JAZZ 0x01
#define PLAYER_TYPE_LORI 0x02
#define PLAYER_TYPE_SPAZ 0x03

/* El cliente envia 3 bytes
    1 byte con ID del cliente
    1 byte con Accion del player
    1 byte con la Direccion (derecha o izquierda)
 Ej:
    A1 12 52 // El player1 camina a la derecha

    A2 15 4C // El player2 dispara a la izquierda
*/


//Estados posibles de un Player
#define STATE_IDLE 0x01
#define STATE_WALK 0x02
#define STATE_RUN 0x03
#define STATE_JUMP 0x04
#define STATE_FALL 0x05
#define STATE_SHOOT 0x06
#define STATE_SPECIAL_ATTACK 0x07
#define STATE_INTOXICATED_IDLE 0x08
#define STATE_INTOXICATED_WALK 0x09
#define STATE_DAMAGED 0x0A
#define STATE_DYING 0x0B
#define STATE_DEAD 0x0C
#define STATE_REVIVE 0x0D

// Enemigos
#define ENEMY_RAT 0xB1
#define ENEMY_BAT 0xB2
#define ENEMY_DIABLO 0xB3

#define ENEMY_STATE_IDLE 0X01
#define ENEMY_STATE_MOVE 0X02
#define ENEMY_STATE_ATTACK 0X03
#define ENEMY_STATE_DAMAGED 0X04
#define ENEMY_STATE_DEATH 0X05

//Armas
#define WEAPON_TYPE1 0XC1
#define WEAPON_TYPE2 0XC2
#define WEAPON_TYPE3 0XC3
#define WEAPON_TYPE4 0XC4


//Items recolectables
#define ITEM_DIAMANTE 0X01
#define ITEM_MONEDA 0X02
#define ITEM_ZANAHORIA 0X03
#define ITEM_MUNCION 0X04
#define ITEM_MUNCION_1 0X05
#define ITEM_MUNCION_2 0X06
#define ITEM_MUNCION_3 0X07
#define ITEM_MUNCION_4 0X08


#endif
