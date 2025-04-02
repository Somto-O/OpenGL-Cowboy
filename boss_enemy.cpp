#include "boss_enemy.h"

namespace game {

BossEnemy::BossEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
    : EnemyGameObject(position, geom, shader, texture, EnemyType::BOSS) {
    health_ = 5;
}

void BossEnemy::Update(double delta_time) {
    // Boss movement and attack behavior will be implemented here
}

} // namespace game
