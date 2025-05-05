#ifndef HEART_H_
#define HEART_H_

#include <iostream>

#include "collectible_game_object.h"


namespace game {

	class Heart : public CollectibleGameObject
	{
	public:
		Heart(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		

		// Update function for any special collectible object updates
		void Update(double delta_time) override;

	private:
		

	};
} // namespace game

#endif 