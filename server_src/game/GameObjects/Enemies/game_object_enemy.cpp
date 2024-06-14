#include "game_object_enemy.h"
#include "../../game_mundo.h"


ObjectEnemy::ObjectEnemy(TipoEnemy tipo, int width, int height,  
                    int damage, int health, 
                    const std::vector<Coordenada>& waypoints) :
    GameObject(width, height),
    tipoEnemy(tipo), damage(damage), health(health), waypoints(waypoints)
{
    type = TypeGameObject::Enemy;
}

void ObjectEnemy::move_x() {
    
}

void ObjectEnemy::take_damage(int &damage) {
    health-=damage;
    if (health <= 0){
        alive = false;
        enemy_status = EstadosEnemy::Death;
    }
}

void ObjectEnemy::attack() {
    enemy_status = EstadosEnemy::Attack;
}

void ObjectEnemy::revive() {
    alive = true;
    enemy_status = EstadosEnemy::Idle;
}

InfoEnemigo ObjectEnemy::getInfo() {
    return InfoEnemigo(tipoEnemy,position.x, position.y, enemy_status);
}

