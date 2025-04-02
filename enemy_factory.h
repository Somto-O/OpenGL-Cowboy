#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include "enemy_game_object.h"
#include "boss_enemy.h"
#include "bandit_enemy.h"
#include "mole_enemy.h"

namespace game {

    class EnemyFactory {
    public:
        static std::unique_ptr<EnemyGameObject> CreateEnemy(EnemyType type,
            const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
    };

} // namespace game
#endif // ENEMY_FACTORY_H_
