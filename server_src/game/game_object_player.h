#ifndef PLAYER_H
#define PLAYER_H

//#include "constantes.h"
#include "game_object.h"
#include "../../common_src/info_juego.h"

#include "Weapons/weapon.h"
#include <cstdint>

//Se debe establecer desde el config.yaml
#define HEALTH 100
#define POINTS 0
#define WALK_SPEED 5
#define INTOXICATED_WALK_SPEED 2
#define RUN_SPEED 10
#define FALL_SPEED 10

//#define LOW_HEALTH 1
#define FULL_HEALTH 10


#define WIDTH_PLAYER 20                                     // (para el futuro Padding de 20px y 11px arriba)
#define HEIGHT_PLAYER 40

// basado en el server_character
class ObjectPlayer : public GameObject {
   
    protected:
        int id;// id de cliente?
        TipoPlayer tipoPlayer;
        EstadosPlayer estado = EstadosPlayer::Inactive;
        int health = 10; //vida
        int points = 0;
        Weapon weapon; //arma
        
        bool alive = true;
        bool intoxicated = false;
        bool falling = false;
        bool tocandoSuelo = true;

    
    private:
        // Mueve las posiciones del gameobject
        //void move(unsigned int x, unsigned int y);
        void move_x(Direcciones direccion, int speed);


    public:
        ObjectPlayer(int id, TipoPlayer &tipo, const Weapon &weapon);
        //ObjectPlayer(int id_player);

        int get_id() {return id;};

        void idle();
        void walk(Direcciones direccion);
        void run(Direcciones direccion);
        void jump(Direcciones direccion);

        void fall();

        //Devuelve true si pudo disparar
        bool shoot(Direcciones direccion);

        //virtual void specialAttack();

    
        bool is_dead() {return alive;};
        bool is_intoxicated() { return intoxicated;};
        bool is_falling() {return falling;};

        void change_weapon(Weapon &&new_weapon);
        
        // recoger municion
        void pick_up_ammo(); 

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void take_damage(int &damage); // health - damage

        void add_points(int points); // points + sum

        void revive();

        InfoPlayer getInfo();
};
#endif
