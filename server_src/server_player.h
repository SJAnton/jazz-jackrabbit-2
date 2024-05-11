#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

#include <cstdint>

#define HEALTH 100
#define POINTS 0
#define X_START 0
#define Y_START 0
#define X_HITBOX 5
#define Y_HITBOX 10
#define JUMP_HEIGHT 10

class Player {
    private:
        // COSAS DEL MUÑECO
        // Crear clase Weapon --> name, ammo, damage, range, rate_of_fire
        // Clase Projectile (bullet, rocket) --> x_pos, y_pos, hitbox_x, hitbox_y, damage
        // El proyectil sale de x_pos + x_hitbox

        // Aumentar vida al comer una zanahoria, reducir al
        // recibir un disparo o ataque de un enemigo
        uint8_t health = HEALTH;

        //Weapon weapon;

        uint8_t points = POINTS;

        uint8_t x_pos = X_START;

        uint8_t y_pos = Y_START;

        // Colisiona con pisos, paredes, techos, enemigos y otros jugadores
        uint8_t x_hitbox = X_HITBOX;

        uint8_t y_hitbox = Y_HITBOX;

        bool alive = true; // Si es false tarda unos segundos en revivir,
                           // aunque puede hacerse con if (health == 0)

        bool intoxicated = false; // No puede disparar si es true, sí moverse

    public:
        Player(); // Puede recibir el Client asociado

        // Getters

        uint8_t get_health();
        
        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t get_left_side(); // Devuelve x_pos - hitbox_x

        uint8_t get_right_side(); // Devuelve x_pos + hitbox_x

        uint8_t get_upper_side(); // Devuelve y_pos + hitbox_y

        uint8_t get_lower_side(); // Devuelve y_pos - hitbox_y

        // Setters

        void set_health(uint8_t new_health);

        void set_x_pos(uint8_t new_x_pos);

        void set_y_pos(uint8_t new_y_pos);

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void take_damage(uint8_t damage);

        void add_points(uint8_t sum);

        void move_x_pos(uint8_t movement); // Toma el byte de movimiento izq/der

        void jump(); // Saltar hasta llegar al tope del salto o hasta tocar el techo

        void fall(); // Caer hasta hacer contacto con el suelo

        void revive();
};
#endif
