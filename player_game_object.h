#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include <iostream>

#include "game_object.h"
#include "timer.h"


namespace game {

    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture);

            int getHealth()const { return health_; }
            Timer getBulletCoolDown()const { return bulletcooldown_; }
            float getPistolReloadSpeed()const { return PistolReloadSpeed_; }
            float getShotGunReloadSpeed()const { return ShotGunReloadSpeed_; }
            void  AddHealth();
           
            // Update function 
            void Update(double delta_time) override;
            Timer bulletcooldown_;
            Timer powerUP_;
            void TakeDamage();
            void addScore() { score_++; };
            int getScore()const { return score_; }
            bool getBlocking()const { return blocking_; }
            void Block() { blocking_ = true; }
            void SetBlocking(bool block){ blocking_ = block; }

    private:
		int health_;
        float PistolReloadSpeed_ = 0.7;
        float ShotGunReloadSpeed_ = 1.5;
        bool blocking_ = false;
        int score_;

    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
