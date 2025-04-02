#ifndef PROJECTILE_GAME_OBJECT_H
#define PROJECTILE_GAME_OBJECT_H

#include <cmath>
#include <iostream>
#include <glm/gtc/constants.hpp>

#include "game_object.h"
#include "timer.h"

namespace game {
	enum class ProjectileState { PISTOL, SHOTGUN };

	class ProjectileGameObject : public GameObject {
	public:
		// Constructor
		ProjectileGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float speed, float angle);

		// Update
		void Update(double delta_time) override;

		// Check if projectile has expired
		bool IsExpired() const;

		// Accessor for previous position
		glm::vec3 GetPreviousPos() const { return prev_pos_; }

		// change texture based on weapon
		void SetTexture(GLuint texture);

		// setter methods for weapon
		void SetWeapon(ProjectileState state) { state_ = state; }
		void Reload(int mag_size);

		// shooting
		void Shoot();

	private:
		// current weapon
		ProjectileState state_;

		// pistol
		GLuint pistol_texture_;

		// shotgun
		GLuint shotgun_texture_;

		// general projectile parameters
		int damage_;
		int magazine_size_;

		float speed_;
		float angle_;
		Timer lifespan_;
		glm::vec3 prev_pos_;

	}; // class ProjectileGameObject
} // namespace game
#endif // PROJECTILE_GAME_OBJECT_H