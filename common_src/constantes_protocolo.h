#ifndef CONSTANTES_PROTOCOLO_H
#define CONSTANTES_PROTOCOLO_H


//Comandos o acciones que puede enviar un Cliente
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
#define STATE_FALL 0x04
#define STATE_SHOOT 0x05
#define STATE_SPECIAL_ATTACK 0x08
#define STATE_INTOXICATED 0x09
#define STATE_DAMAGED 0x0A
#define STATE_DYING 0x0B
#define STATE_DEAD 0x0C
#define STATE_REVIVE 0x0D

//Tipos de Eventos
#define PLAYER_CAMBIA_ESTADO 0xE1
#define PLAYER_SUMA_PUNTOS 0xE2
#define ENEMIGO_CAMBIA_ESTADO 0xE3
#define MONEDA_RECOLECTADA 0xE5



/* El server devuelve a todos los clientes:
    1 byte con el tipo de Evento
    si es E1:
        1 byte con el ID del player
        1 byte con el estado del Player
        4 bytes con la posicion xy
    si es E2:
        1 byte con el ID del player
        2 bytes con el puntaje del player
    si es E3:
        1 byte con el ID del enemigo
        1 byte con el estado del Enemigo
        4 bytes con la posicion (suponiendo que se pueden mover)
    si es E4:
        1 byte con el ID de la moneda (u otra forma de identificarla)
    
    ultimo byte con 0x00

*/

#endif
