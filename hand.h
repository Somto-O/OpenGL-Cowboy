#ifndef HAND_H_
#define HAND_H_

#include <iostream>

#include "game_object.h"
#include "LowerArm.h"
#include "timer.h"


namespace game {

	class Hand : public GameObject
	{
	public:
		Hand(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, LowerArm* origin);

		

		// Update function for any special collectible object updates
		void Update(double delta_time) override;
		Timer explosionReady_;
	private:
		LowerArm*  origin_;
		bool side_;
		



	};
} // namespace game

#endif 