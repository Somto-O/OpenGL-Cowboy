#ifndef SHIELD_H_
#define SHIELD_H_

#include <iostream>

#include "collectible_game_object.h"


namespace game {

	class Shield : public CollectibleGameObject
	{
	public:
		Shield(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		

		// Update function for any special collectible object updates
		void Update(double delta_time) override;

	private:
		

	};
} // namespace game

#endif 