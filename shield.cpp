#include <glm/gtc/constants.hpp>

#include "shield.h"

namespace game {


	Shield::Shield(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: CollectibleGameObject(position, geom, shader, texture)
	{
		SetScale(0.5);
	}


	void Shield::Update(double delta_time) {

		// Special collectible updates go here
	}

} // namespace game