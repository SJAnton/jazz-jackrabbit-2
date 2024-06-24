#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

//#include "constantes.h"
#include "../game_object.h"
#include "../Projectile/game_object_projectile.h"

#include "../../../../common_src/info_juego.h"

#include "../../Weapons/weapon.h"


//#define WIDTH_PLAYER 20  // (para el futuro Padding de 20px y 11px arriba)
//#define HEIGHT_PLAYER 40

// constantes de cuantas iteraciones duran la animaciones
#define TIME_JUMP 16//12
#define TIME_SHOOT 6
#define TIME_DEATH 60 // 4 seg

#define TIME_DYING_SPAZ 13 // (no tiene la misma duracion que las otras)
#define TIME_DYING_LORI 20
#define TIME_DYING_JAZZ 20

#define ITR_PER_SEC 15
#define DAMAGE_WAIT_TIME 1 // Segundos

// basado en el server_character
class ObjectPlayer : public GameObject {
   protected:
        static bool inicializado;

        //Constantes inicializadas en la funcion init() (llamado en Game::init())
        static int defaultHealth;
        static int defaultDamageAttack;
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
        Weapon *weapon; //arma
        std::vector<Weapon> weapons; //armas
        int weaponIndex = 0; //indice del arma actual

        bool alive = true;
        bool intoxicated = false;
        bool falling = true;
        bool is_jumping = false;
        bool tocandoSuelo = false;
        bool isDoingSpecialAttack = false;
        bool can_take_damage = true;

        int health_buffer = 0;
        int damage_wait_time = DAMAGE_WAIT_TIME * ITR_PER_SEC;
        int damage_wait_buffer = DAMAGE_WAIT_TIME * ITR_PER_SEC;

    public:
        // los timer los maeja el game
        int timer_jump = 0; // Variable auxiliar para saber en que iteracion del salto está
        int timer_shoot = 0; // Variable auxiliar para saber cuantas iterciones pasaron desde el disparo
        int timer_specialAttack = 0; // Variable auxiliar para saber cuantas iterciones van desde que inició el ataque especial

        int timer_dying = 0; // Variable auxiliar para saber en que iteracion del estado muriendo
        int timer_death = 0; // Variable auxiliar para saber cuantas iterciones lleva muerto
        bool is_dying = false; // cuando se esta ejecutando la animacion de morir

    protected:
        // Mueve las posiciones del gameobject
        bool move_x(Direcciones direccion, int speed);
        bool move_y(int speed);
        bool down_y(int spped);
        int getTimeDying();

    public:
        // inicializo todas las constantes de los Players una unica vez
        static void init(int health, int damage_attack, int speed_walk, int speed_run, int speed_intoxicated, int speed_jump, int speed_fall);
    
        ObjectPlayer(int id, const TipoPlayer &tipo);

        // Movimientos y Acciones

        void idle();
        
        void walk(Direcciones direccion);

        void run(Direcciones direccion);
        
        //Hace un movimiento de parábola
        void jump(Direcciones direccion);

        void fall();
        virtual void specialAttack() {}; // no implementado

        int getSpecialAttackDamage();

        // Devuelve el proyectil disparado
        ObjectProjectile shoot(Direcciones direccion);

        //getters

        int get_id() {return id;};

        int get_points() {return points;};

        Weapon get_weapon() {return *weapon;};

        bool is_dead() {return !alive;};
        bool is_intoxicated() { return intoxicated;};
        bool is_falling() {return falling;};
        bool isJumping() {return is_jumping;}
        bool is_doing_specialAttack() {return isDoingSpecialAttack;};
        bool can_be_damaged() {return can_take_damage;};

        EstadosPlayer getEstado();
        //Setters
        
        void change_weapon();
        
        void pick_up_ammo(int ammo, int weaponIndex); // recoger municion

        void initialize_weapons();

        void add_hearts(int pts_vidas); // Suma vida. Si recibe un negativo era una zanahoria envenenada

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void set_jumping_status(const bool &status);

        void take_damage(int &damage); // health - damage

        void add_points(int points); // points + sum
        

        void death();

        // actualiza los timers y cambia el estado de dying a death cuando corresponda
        void updateDeath();
        void updateJump();
        void updateShoot();
        void updateShootingDelay();
        void updateDamageWaitTime();
        virtual void updateSpecialAttack() {};

        void revive();

        InfoPlayer getInfo();
};
#endif
