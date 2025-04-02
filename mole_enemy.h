#ifndef MOLE_ENEMY_H_
#define MOLE_ENEMY_H_

#include "enemy_game_object.h"

namespace game {

class MoleEnemy : public EnemyGameObject {
    public:
        MoleEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        void Update(double delta_time) override;
};

} // namespace game
#endif // MOLE_ENEMY_H_
