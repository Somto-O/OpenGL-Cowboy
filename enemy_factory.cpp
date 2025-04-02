#include "enemy_factory.h"

namespace game {

    std::unique_ptr<EnemyGameObject> EnemyFactory::CreateEnemy(EnemyType type,
        const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) {

        switch (type) {
        case EnemyType::BOSS:
            return std::make_unique<BossEnemy>(position, geom, shader, texture);
        case EnemyType::BANDIT:
            return std::make_unique<BanditEnemy>(position, geom, shader, texture);
        case EnemyType::MOLE:
            return std::make_unique<MoleEnemy>(position, geom, shader, texture);
        default:
            return nullptr; // Fallback case
        }
    }

} // namespace game
