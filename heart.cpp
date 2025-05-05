#include <glm/gtc/constants.hpp>

#include "heart.h"

namespace game {


	Heart::Heart(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: CollectibleGameObject(position, geom, shader, texture)
	{
		SetScale(0.5);
	}


	void Heart::Update(double delta_time) {

		// Special collectible updates go here
	}

} // namespace game