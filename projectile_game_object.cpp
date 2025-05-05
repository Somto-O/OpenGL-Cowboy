#include "projectile_game_object.h"

namespace game {
    // Constructor
    ProjectileGameObject::ProjectileGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float speed, float angle, ProjectileState state, GameObject* owner)
        : GameObject(position, geom, shader, texture), speed_(speed), angle_(angle), state_(state),
        damage_(0),
        magazine_size_(0)
    {
        lifespan_.Start(3.0f);
        prev_pos_ = position;
        SetRotation(angle); // Set the initial rotation to the angle
        SetScale(1.0f); // Set initial scale
        owner_ = owner;
    }

    // Update
    void ProjectileGameObject::Update(double delta_time)
    {
        // Store previous position before updating
        prev_pos_ = GetPosition();

        if (state_ == ProjectileState::PISTOL)
        {

            // Get position and move in the direction of the angle
            glm::vec3 pos = GetPosition();
            pos.x += speed_ * cos(angle_) * static_cast<float>(delta_time);
            pos.y += speed_ * sin(angle_) * static_cast<float>(delta_time);
            SetPosition(pos);
            SetRotation(angle_ + (3.0f * glm::pi<float>()) / 2.0f); // Rotate the texture to match the angle
            SetScale(0.3f); // Set scale for pistol

        }
        else if (state_ == ProjectileState::SHOTGUN)
        {

            // Get position and move in the direction of the angle
            glm::vec3 pos = GetPosition();
            pos.x += (speed_ - 0.5f) * cos(angle_) * static_cast<float>(delta_time);
            pos.y += (speed_ - 0.5f) * sin(angle_) * static_cast<float>(delta_time);
            SetPosition(pos);
            SetRotation(angle_ + (3.0f * glm::pi<float>()) / 2.0f); // Rotate the texture to match the angle
            SetScale(0.3f); // Set scale for shotgun
            
          
           
        }
    }

    bool ProjectileGameObject::IsExpired() const
    {
        return lifespan_.Finished();
    }

} // namespace game
