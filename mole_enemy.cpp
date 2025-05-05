#include "mole_enemy.h"
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>

namespace game {

MoleEnemy::MoleEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture,PlayerGameObject* player)
    : EnemyGameObject(position, geom, shader, texture, EnemyType::MOLE, player) 
{
    startTime_ = glfwGetTime();
    width_ = 0.5;
    height_ = 0.5;
    circle_ = glm::vec3(width_ + GetPosition().x, height_ + GetPosition().y, 0.0f);
    health_ = 2;
    fatness = 0.7;
    angry = false;
}

void MoleEnemy::Update(double delta_time) {
    if (angry) {


        SetRotation(-glm::pi<float>() / 2.0f);

        glm::vec3 player_position = player_->GetPosition();

        glm::vec3 mole_position = GetPosition();

        glm::vec3 direction = player_position - mole_position;

        // Normalize the direction vector to get the unit vector
        direction = glm::normalize(direction);

        float speed = 1.0f;

        // Calculate the new position based on the direction and speed
        glm::vec3 new_position = mole_position + direction * static_cast<float>(delta_time) * speed;

        SetPosition(new_position);

        float angle = atan2(direction.y, direction.x);
        SetRotation(angle);
    }
    else {
        glm::vec3 dir = GetBearing();
        double passedTime = glfwGetTime() - startTime_;
        glm::vec3 position = glm::vec3(2 * cos(passedTime) + circle_.x, sin(passedTime) + circle_.y, 0.0f);


        SetPosition(position);



    }

    float distance = glm::length(GetPosition() - player_->GetPosition());
    if (distance < 2.0f) {
        angry = true;
    }
}

} // namespace game
