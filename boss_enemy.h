#ifndef BOSS_ENEMY_H_
#define BOSS_ENEMY_H_

#include "enemy_game_object.h"


namespace game {

class BossEnemy : public EnemyGameObject {
    public:
        BossEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture,PlayerGameObject* player);

        void Update(double delta_time) override;

    private:
        
    
        


};

} // namespace game
#endif // BOSS_ENEMY_H_
