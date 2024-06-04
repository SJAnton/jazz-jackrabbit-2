#ifndef CONSTANTES_PROTOCOLO_H
#define CONSTANTES_PROTOCOLO_H

#define SIZE_CLIENT_MSG 3

#define LENGTH_PLAYER_INFO 10
#define LENGTH_ENEMY_INFO 6
#define LENGTH_ITEMS_INFO 5
#define LENGTH_PROYECTIL_INFO 5

//Comandos o acciones que puede enviar un Cliente
#define ACTION_IDLE 0x11
#define ACTION_WALK 0x12
#define ACTION_RUN 0x13
#define ACTION_JUMP 0x14
#define ACTION_SHOOT 0x15
#define ACTION_SPECIAL_ATACK 0x16
// La accion vendrá seguida de la direccion en el eje x
#define LEFT 0x4C // L
#define RIGHT 0x52 // R

//ID para identificar el cliente al que le corresponde la accion o el estado
#define PLAYER_1 0xA1
#define PLAYER_2 0xA2
#define PLAYER_3 0xA3
#define PLAYER_4 0xA4


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
#define ENEMY_LIZARD 0xB3

#define ENEMY_STATE_IDLE 0X01
#define ENEMY_STATE_MOVE 0X02
#define ENEMY_STATE_ATTACK 0X03
#define ENEMY_STATE_DAMAGED 0X04
#define ENEMY_STATE_DEATH 0X05


#endif
