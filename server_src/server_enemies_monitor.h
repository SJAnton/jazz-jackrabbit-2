#ifndef SERVER_ENEMIES_MONITOR_H
#define SERVER_ENEMIES_MONITOR_H


#include <map>
#include <mutex>
#include <memory>

#include "characters/server_character.h"

// Include any necessary headers here

class ServerEnemiesMonitor {
private:

    // Add your class members and methods here
    std::map<int, std::shared_ptr<Character>> map;

    std::mutex m;
    // Add any private members or helper functions here
public:
    ServerEnemiesMonitor() {};

    void push_back(int id, std::shared_ptr<Character> character);

    std::shared_ptr<Character> at(int id);

    int size();

    bool is_empty();

    void erase(int id);

    void clear();

    std::map<int, std::shared_ptr<Character>>::iterator begin();

    std::map<int, std::shared_ptr<Character>>::iterator end();

    // Add any public members or helper functions here
    void update(int id, std::shared_ptr<Character> character);
    
    /*
    void update_health(int id, uint8_t health);
    void update_points(int id, uint8_t points);
    void update_position(int id, uint8_t x_pos, uint8_t y_pos);
    void update_hitbox(int id, uint8_t x_hitbox, uint8_t y_hitbox);
    void update_alive(int id, bool alive);
    void update_frozen(int id, bool frozen);
    void update_intoxicated(int id, bool intoxicated);
    void update_weapon(int id, Weapon weapon);
    void update_player_id(int id, int player_id);
    void update_enemy_id(int id, int enemy_id);
    */
};

#endif // SERVER_ENEMIES_MONITOR_H