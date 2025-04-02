#include <glm/gtc/constants.hpp>

#include "player_game_object.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/
PlayerGameObject::PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
	: GameObject(position, geom, shader, texture), health_(3)
{

}


// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {

	// Special player updates go here
}

// any other player specific methods go here


} // namespace game
