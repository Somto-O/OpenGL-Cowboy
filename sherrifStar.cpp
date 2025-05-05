#include <glm/gtc/constants.hpp>

#include "sherrifStar.h"

namespace game {


	SherrifStar::SherrifStar(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: CollectibleGameObject(position, geom, shader, texture)
	{

	}


	void SherrifStar::Update(double delta_time) {

		// Special collectible updates go here
	}

} // namespace game