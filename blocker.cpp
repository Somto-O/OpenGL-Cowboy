#include <glm/gtc/constants.hpp>

#include "blocker.h"

namespace game {


	Blocker::Blocker(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player)
		: GameObject(position, geom, shader, texture)
	{
		player_ = player;
		SetScale(0.5);
	}


	void Blocker::Update(double delta_time) {

		SetPosition(glm::vec3(player_->GetPosition().x, player_->GetPosition().y+1, 0.0f));
	}

} // namespace game