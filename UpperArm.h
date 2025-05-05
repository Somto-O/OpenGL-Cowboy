#ifndef UPPERARM_H_
#define UPPERARM_H_

#include <iostream>
#include "boss_enemy.h"
#include "Timer.h"

#include "game_object.h"


namespace game {

	class UpperArm : public GameObject
	{
	public:
		UpperArm(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, BossEnemy* origin, bool side);

		bool getSide() const{ return side_; }

		// Update function for any special collectible object updates
		void Update(double delta_time) override;

	private:
		bool side_ = false;
		BossEnemy* origin_;
		Timer switchTime_;
		bool direction_;

	};
} // namespace game

#endif 