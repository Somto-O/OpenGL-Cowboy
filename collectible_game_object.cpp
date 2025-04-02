#include <glm/gtc/constants.hpp>

#include "collectible_game_object.h"

namespace game {


CollectibleGameObject::CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
	: GameObject(position, geom, shader, texture)
{

}


void CollectibleGameObject::Update(double delta_time) {

	// Special collectible updates go here
}

// any other collectible specific methods go here

} // namespace game