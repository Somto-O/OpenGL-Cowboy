#include "bandit_enemy.h"
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>

namespace game {

    BanditEnemy::BanditEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player)
        : EnemyGameObject(position, geom, shader, texture, EnemyType::BANDIT, player) {
        buildUp_.Start(3);
        turnTime_.Start(4);
        health_ = 4;
        fatness = 0.5;
    
    }

    void BanditEnemy::Update(double delta_time) {

        SetRotation(-glm::pi<float>() / 2.0f);
        if (angry_) {
            
            if (player_->GetPosition().x > position_.x) {
                SetPosition(glm::vec3(position_.x + 0.01, position_.y, 0.0f));

            }
            if (player_->GetPosition().x < position_.x) {
                SetPosition(glm::vec3(position_.x - 0.01, position_.y, 0.0f));
            }
            if (enraged_.Finished()) {
                angry_ = false;
                buildUp_.Start(2);
              
            }
            
        }
        else {
            

            if (buildUp_.Finished()) {
                angry_ = true;
                enraged_.Start(2);
            }
            if (turnTime_.Finished()) {
                left = !left;
                turnTime_.Start(4);
            }
            if (left) {
                SetPosition(glm::vec3(position_.x - 0.001, position_.y, 0.0f));
            }
            else {
                SetPosition(glm::vec3(position_.x + 0.001, position_.y, 0.0f));
            }
            
        }

        if (position_.y - player_->GetPosition().y < 4) {
            SetPosition(glm::vec3(position_.x, position_.y+0.001, 0.0f));
        }
        if (position_.y - player_->GetPosition().y > 5) {
            SetPosition(glm::vec3(position_.x, position_.y - 0.001, 0.0f));
        }

    }
    
}