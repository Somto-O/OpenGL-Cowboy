#include "enemy_factory.h"  

namespace game {

    EnemyGameObject* EnemyFactory::CreateEnemy(EnemyType type,
        const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player) {
        switch (type) {
        //case EnemyType::BOSS:
           // return new BossEnemy(position, geom, shader, texture, player);
        case EnemyType::BANDIT:
            return new BanditEnemy(position, geom, shader, texture, player);
        case EnemyType::MOLE:
            return new MoleEnemy(position, geom, shader, texture, player);
        default:
            return nullptr;
        }
    }

} // namespace game
