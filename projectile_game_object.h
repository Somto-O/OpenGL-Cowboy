#ifndef PROJECTILE_GAME_OBJECT_H
#define PROJECTILE_GAME_OBJECT_H

#include <cmath>
#include <iostream>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "player_game_object.h"
#include "game_object.h"
#include "timer.h"

namespace game {
	enum class ProjectileState { PISTOL, SHOTGUN };

	class ProjectileGameObject : public GameObject {
	public:
		// Constructor
		ProjectileGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float speed, float angle, ProjectileState state, GameObject* Owner);

		// Update
		void Update(double delta_time) override;

		// Check if projectile has expired
		bool IsExpired() const;

		// Accessors
		glm::vec3 GetPreviousPos() const { return prev_pos_; }
		ProjectileState GetWeapon() const { return state_; }

		// setter methods for weapon
		void SetWeapon(ProjectileState state) { state_ = state; }

		// set angle
		void SetAngle(float angle) { angle_ = angle; }
		float getAngle()const { return angle_; }

		GameObject* getOwner() const { return owner_; }
		void setOwner(GameObject* newOwner) { owner_ = newOwner; }

	private:
		// current weapon
		ProjectileState state_;

		// general projectile parameters
		int damage_;
		int magazine_size_;

		float speed_;
		float angle_;
		Timer lifespan_;
		glm::vec3 prev_pos_;
		GameObject* owner_;

	}; // class ProjectileGameObject
} // namespace game
#endif // PROJECTILE_GAME_OBJECT_H
