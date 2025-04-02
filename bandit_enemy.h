#ifndef BANDIT_ENEMY_H_
#define BANDIT_ENEMY_H_

#include "enemy_game_object.h"

namespace game {

class BanditEnemy : public EnemyGameObject {
    public:
        BanditEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        void Update(double delta_time) override;
};

} // namespace game
#endif // BANDIT_ENEMY_H_
