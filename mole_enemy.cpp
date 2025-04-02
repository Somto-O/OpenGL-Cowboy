#include "mole_enemy.h"

namespace game {

MoleEnemy::MoleEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
    : EnemyGameObject(position, geom, shader, texture, EnemyType::MOLE) {
    health_ = 1;
}

void MoleEnemy::Update(double delta_time) {
    // Mole popping behavior will be implemented here
}

} // namespace game
