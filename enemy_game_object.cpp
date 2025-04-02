#include <glm/gtc/constants.hpp>

#include "enemy_game_object.h"

namespace game {

	EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, EnemyType type)
		: GameObject(position, geom, shader, texture),
		  type_(type)
	{

	}


	void EnemyGameObject::Update(double delta_time)
	{
		// Special enemy updates go here
	}

} // namespace game


