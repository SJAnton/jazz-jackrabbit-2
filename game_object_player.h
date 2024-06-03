#ifndef PLAYER_H
#define PLAYER_H

#include "constantes.h"
#include "game_object.h"


#include <cstdint>


#define HEALTH 100
#define POINTS 0

#define WIDTH_PLAYER 20/4                                     // (para el futuro Padding de 20px y 11px arriba)
#define HEIGHT_PLAYER 40/4

// basado en el server_character
class ObjectPlayer : public GameObject{
    private:

    protected:
        EstadosPlayer estado = EstadosPlayer::Inactive;
        int player_id;
        int health = 10; //vida
        int points = 0;

        int x_hitbox = 1; //velocidad x
        int y_hitbox = 1; //velocidad y
        
        //Weapon weapon; // Arma

        bool alive = true;
        bool frozen = false; 
        bool intoxicated = false;

    
    private:
        // Mueve las posiciones del gameobject
        void move(unsigned x, unsigned int y);

        //void move_x_pos(uint8_t &movement, uint8_t &direction);

    public:
        ObjectPlayer();
        ObjectPlayer(int id_player);

        int get_id();

        //uint8_t left_side(); // Devuelve x_pos - hitbox_x
        //uint8_t right_side(); // Devuelve x_pos + hitbox_x
        //uint8_t upper_side(); // Devuelve y_pos + hitbox_y
        //uint8_t lower_side(); // Devuelve y_pos - hitbox_y
        void walk(Direcciones direccion);
        void run(Direcciones direccion);
        void jump();
        void fall();
        void shoot();
        //virtual void specialAttack();

        

        bool is_dead();

        bool is_frozen();

        bool is_intoxicated();

        //void move(uint8_t x, uint8_t y);

        //void move_x_pos(uint8_t &movement, uint8_t &direction);

        //void attack();

        //void special_attack();

        //void change_weapon(Weapon &&new_weapon);
        //void pick_up_ammo(); // recoger municion


        void set_frozen_status(bool status);

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void take_damage(uint8_t &damage); // health - damage

        void add_points(int points); // points + sum

        void revive();
};
#endif
