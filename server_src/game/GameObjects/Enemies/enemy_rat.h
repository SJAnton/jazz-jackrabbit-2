#ifndef OBJECT_ENEMY_RAT
#define OBJECT_ENEMY_RAT

#include "game_object_enemy.h"

#define WIDTH_RAT 80
#define HEIGHT_RAT 40

class EnemyRat : public ObjectEnemy
{
private:
    static bool initialized;
    static int Default_Damage;
    static int Default_Health;
public:
    static void init(int damage, int health);
    EnemyRat(const std::vector<Coordenada>& waypoints) : 
        ObjectEnemy(TipoEnemy::Rat, WIDTH_RAT, HEIGHT_RAT, Default_Damage, Default_Health, waypoints)
    {}

};
#endif //OBJECT_ENEMY_RAT
