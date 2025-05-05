#include "boss_enemy.h"
#include <glm/gtc/constants.hpp>


namespace game {

BossEnemy::BossEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player)
    : EnemyGameObject(position, geom, shader, texture, EnemyType::BOSS, player) 
{
    health_ = 9;
    SetScale(5);
    fatness = 2.0;

    
   
}

void BossEnemy::Update(double delta_time) {    
   

    
}

} // namespace game
