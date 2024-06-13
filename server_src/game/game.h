#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "../server_queue.h"
#include "../server_queue_list.h"
#include "../server_character_map.h"
#include "../../common_src/info_juego.h"
#include "game_mundo.h"

class Game {
    private:
        bool _is_running = true;
        //std::vector<ObjectPlayer> players;
        //std::shared_ptr<PlayerMap> ch_map; //Lista de Players
        std::shared_ptr<PlayerMap> ch_map;// = std::make_shared<PlayerMap>(); // Inicialización del shared_ptr
        std::vector<ObjectCollected> itemsRecolectables;
        GameMundo gameMundo;

        //std::list<std::shared_ptr<Projectile>> &projectile_list;

    public:
        Game();

        std::vector<uint8_t> get_actions(std::shared_ptr<Queue<uint8_t>> &q);
        void update();

        void execute_actions(std::vector<uint8_t> &actions);
        //void execute_actions(const int &id_client, const AccionesPlayer &accion);

        //void tick(std::list<std::shared_ptr<Projectile>> &projectile_list);

        InfoJuego snapshot();

        void send_snapshot(ServerQueueList &sndr_qs);

        void add_player(TipoPlayer &player_type, int player_id);

        void remove_player(uint8_t &player_id);
        
        bool is_running();
};
#endif
