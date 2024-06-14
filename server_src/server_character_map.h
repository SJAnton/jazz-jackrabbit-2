#ifndef SERVER_Player_MAP_H_
#define SERVER_Player_MAP_H_

#include <map>
#include <mutex>
#include <memory>

//#include "Players/server_Player.h"
#include "game/GameObjects/Players/game_object_player.h"

class PlayerMap {
    private:
        std::map<int, std::shared_ptr<ObjectPlayer>> map;

        std::mutex m;

    public:
        PlayerMap() {};

        void push_back(int id, std::shared_ptr<ObjectPlayer> &ObjectPlayer);

        std::shared_ptr<ObjectPlayer> at(int id);

        int size();

        bool empty();

        void erase(int id);

        void clear();

        std::map<int, std::shared_ptr<ObjectPlayer>>::iterator begin();

        std::map<int, std::shared_ptr<ObjectPlayer>>::iterator end();
        std::vector<std::shared_ptr<ObjectPlayer>> getPlayers();

};
#endif
