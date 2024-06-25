#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "game_mundo.h"
#include "Map/game_map_reader.h"
#include "../../common_src/info_juego.h"
#include "GameObjects/Players/player_Spaz.h"
#include "GameObjects/Players/player_Lori.h"
#include "GameObjects/Players/player_Jazz.h"

class Game {
    public:
        // Carga los valores del config.yaml
        static void init(std::map<std::string, std::vector<int>> &config);
        
    private:
        bool _is_running = true;

        std::shared_ptr<PlayerMap> ch_map;
        std::vector<std::shared_ptr<ObjectEnemy>> enemies; //lista con todos los enemigos del juego
        std::vector<ObjectCollected> itemsRecolectables;

        std::vector<std::shared_ptr<ObjectPlayer>> top_players;

        GameMundo gameMundo;

        static int timeLeftInit; // constante para guardarme el tiempo de duracion de la partida.
        int timeleft; // variable para el tiempo restante

        static bool compare_points(
            std::shared_ptr<ObjectPlayer> &pl1, std::shared_ptr<ObjectPlayer> &pl2
        );

        void update_top_players();

        int auxJump = 0; //variable auxiliar para llevar el conteo de veces que se llama a player->jump
        //establesco el tiempo que dura el salto en 4 iteraciones 
        int timeJump = 7; //   (ajustar segun la vel de salto y visualmente)

    public:
        Game(Level &level);

        void update();
        
        // Resta un segundo
        void minusTimeLeft();
        int getTimeLeft();

        void execute_actions(std::vector<uint8_t> &actions);

        InfoJuego snapshot();

        void add_player(TipoPlayer &player_type, int player_id);

        void add_player(TipoPlayer &player_type, int player_id, Coordenada spawn);

        void remove_player(const int &player_id);
        
        bool is_running();

        void stop();
};
#endif
