#ifndef SERVER_PROJECTILE_H_
#define SERVER_PROJECTILE_H_

#include <vector>
#include <cstdint>
#include <stdexcept>

#include "../../../common_src/info_juego.h"
#include "../../../common_src/constantes_protocolo.h"

#define PR_ID_POS 0
#define PR_RD_POS 1
#define PR_DM_POS 2
#define PR_MP_POS 3
#define PR_SP_POS 4

#define RK_ID_POS 0
#define RK_XH_POS 1
#define RK_YH_POS 2
#define RK_DM_POS 3
#define RK_MP_POS 4
#define RK_SP_POS 5

class Projectile {
    // De esta clase heredan todos los proyectiles
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    private:
        //bool contact_x(Character &ch);

        //bool contact_y(Character &ch);

    protected:
        uint8_t projectile_id;

        Direcciones direction;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

        uint8_t speed;

        bool powered_up = false;

    public:
        Projectile();

        InfoProyectil set_data();

        uint8_t get_id();

        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t left_side();

        uint8_t right_side();

        uint8_t upper_side();

        uint8_t lower_side();

        bool is_powered_up();

        void move(uint8_t x, uint8_t y);

        void move_x_pos();

        void move_y_pos();

        void power_up();

        void power_up_end();

        //bool contact(Character &ch);
};
#endif
