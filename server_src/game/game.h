#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

//#include "../../common_src/queue.h"
//#include "../server_queue_list.h"
//#include "../server_character_map.h"
#include "../../common_src/info_juego.h"
#include "game_mundo.h"
#include "GameObjects/Players/player_Spaz.h"
#include "GameObjects/Players/player_Lori.h"
#include "GameObjects/Players/player_Jazz.h"

class Game {
    public:
        /*
         * necesito recibir:
         * Terreno (clase que contenga una matriz (30x30) que me diga si un tile es solido o no)
         * (NADA MAS!)
         * Cantidad de enemigos, tipos y sus posiciones.
         * Cantidad de items, tipo y sus posiciones.
         * 
        */

        // Carga los valores del config.yaml
        static void init(std::map<std::string, std::vector<uint8_t>> &config);
        
    private:
        bool _is_running = true;

        std::shared_ptr<PlayerMap> ch_map;
        std::vector<std::shared_ptr<ObjectEnemy>> enemies; //lista con todos los enemigos del juego
        std::vector<ObjectCollected> itemsRecolectables;


        GameMundo gameMundo;


        int auxJump = 0; //variable auxiliar para llevar el conteo de veces que se llama a player->jump
        //establesco el tiempo que dura el salto en 4 iteraciones 
        int timeJump = 7; //   (ajustar segun la vel de salto y visualmente)

    public:
        Game();

        void update();

        void execute_actions(std::vector<uint8_t> &actions);

        InfoJuego snapshot();

        void add_player(TipoPlayer &player_type, int player_id);

        void remove_player(const int &player_id);
        
        bool is_running();

        void stop();
};
#endif
