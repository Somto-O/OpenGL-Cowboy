#ifndef BANDIT_ENEMY_H_
#define BANDIT_ENEMY_H_

#include "enemy_game_object.h"
#include "timer.h"

namespace game {

class BanditEnemy : public EnemyGameObject {
    public:
        BanditEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player);

        void Update(double delta_time) override;

   private:
       bool angry_ = false;
       Timer enraged_;
       Timer buildUp_;
       Timer turnTime_;
       bool left = true;
       
      
};

} // namespace game
#endif // BANDIT_ENEMY_H_
