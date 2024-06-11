#ifndef SERVER_GAMELOOP_LIST_H_
#define SERVER_GAMELOOP_LIST_H_

#include <list>
#include <mutex>

#include "server_gameloop.h"

class GameloopList {
    private:
        std::list<ServerGameloop*> list;

        std::mutex m;
        
    public:
        GameloopList() {};

        void push_back(ServerGameloop *gameloop);

        void remove(ServerGameloop *gameloop);

        int size();

        void clear();

        std::list<ServerGameloop*>::iterator erase(std::list<ServerGameloop*>::iterator it);

        std::list<ServerGameloop*>::iterator begin();

        std::list<ServerGameloop*>::iterator end();

        ServerGameloop* find_by_id(int id);
};
#endif
