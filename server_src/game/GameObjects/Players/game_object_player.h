#ifndef PLAYER_H
#define PLAYER_H

//#include "constantes.h"
#include "../game_object.h"
#include "../Projectile/game_object_projectile.h"

#include "../../../../common_src/info_juego.h"

#include "../../Weapons/weapon.h"
#include <cstdint>

#define WIDTH_PLAYER 20  // (para el futuro Padding de 20px y 11px arriba)
#define HEIGHT_PLAYER 40

// basado en el server_character
class ObjectPlayer : public GameObject {
   protected:
        static bool inicializado;

        //Constantes inicializadas en la funcion init() (llamado en Game::init())
        static int defaultHealth;
        static int defaultWalkSpeed;
        static int defaultRunSpeed;
        static int defaultIntoxicatedSpeed;
        static int defaultJumpSpeed;
        static int defaultFallSpeed;

    protected:
        int id;// id de cliente?
        TipoPlayer tipoPlayer;
        EstadosPlayer estado = EstadosPlayer::Inactive;
        Direcciones direction = Right;
        int health = 10; //vida
        int points = 0;
        Weapon weapon; //arma
        
        bool alive = true;
        bool intoxicated = false;
        bool falling = false;
        bool tocandoSuelo = true;
        bool jumping = false;

    private:
        // Mueve las posiciones del gameobject
        //void move(unsigned int x, unsigned int y);
        void move_x(Direcciones direccion, int speed);


    public:
        // inicializo todas las constantes de los Players una unica vez
        static void init(int health, int speed_walk, int speed_run, int speed_intoxicated, int speed_jump, int speed_fall);
    
        ObjectPlayer(int id, TipoPlayer &tipo, const Weapon &weapon);

// Movimientos y Acciones

        void idle();
        void walk(Direcciones direccion);
        void run(Direcciones direccion);
        
        //Hace un movimiento de parábola
        void jump(Direcciones direccion);
        void fall();
        //virtual void specialAttack(); // no implementado

        /**
         * Devuelve el proyectil disparado
        */
        ObjectProjectile shoot(Direcciones direccion);

//getters

        int get_id() {return id;};
        bool is_dead() {return alive;};
        bool is_intoxicated() { return intoxicated;};
        bool is_falling() {return falling;};
        bool isJumping() {return jumping;}

    //Setters

        void change_weapon(Weapon &&new_weapon);
        
        // recoger municion
        void pick_up_ammo(int ammo); 

        void add_hearts(int pts_vidas); // Suma vida. Si recibe un negativo era una zanahoria envenenada

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false
        void set_jumping_status(const bool &status);
        void take_damage(int &damage); // health - damage

        void add_points(int points); // points + sum

        void revive();

        InfoPlayer getInfo();
};
#endif
