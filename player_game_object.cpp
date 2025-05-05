#include <glm/gtc/constants.hpp>

#include "player_game_object.h"

namespace game {

	/*
		PlayerGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/
	PlayerGameObject::PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture), health_(5)
	{
		score_ = 0;
	}


	// Update function for moving the player object around
	void PlayerGameObject::Update(double delta_time) {
		
		if (powerUP_.Finished()) {
			PistolReloadSpeed_ = 0.7;
			ShotGunReloadSpeed_ = 1.5;
		}
		else {
			PistolReloadSpeed_ = 0.2;
			ShotGunReloadSpeed_ = 0.6;
		}
	}

	// any other player specific methods go here
	void PlayerGameObject::TakeDamage() {
		health_--;
		std::cout << "Player took damage! Health: " << health_ << std::endl;
		if (health_ <= 0) {
			health_ = 0;
			std::cout << "Player is dead!" << std::endl;
		}
	}

	void  PlayerGameObject::AddHealth() {
		if (health_ < 5) {
			health_++;
		}
	}

} // namespace game
