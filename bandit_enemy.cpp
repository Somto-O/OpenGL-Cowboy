#include "bandit_enemy.h"

namespace game {

BanditEnemy::BanditEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
    : EnemyGameObject(position, geom, shader, texture, EnemyType::BANDIT) {
    health_ = 2;
}

void BanditEnemy::Update(double delta_time) {
    // Bandit attack and movement behavior will be implemented here
}

} // namespace game
