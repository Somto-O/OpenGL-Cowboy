#include <glm/gtc/constants.hpp>

#include "Tnt.h"

namespace game {


	Tnt::Tnt(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player)
		: GameObject(position, geom, shader, texture)
	{
		velo_ = (player->GetPosition() - position);
		dir_ = player->GetPosition() - position_;
		target_ = player->GetPosition();

	}


	void Tnt::Update(double delta_time) {

		position_ = position_ + velo_ * float(delta_time);

		


	}

} // namespace game