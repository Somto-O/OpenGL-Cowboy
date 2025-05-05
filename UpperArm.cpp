#include <glm/gtc/constants.hpp>

#include "UpperArm.h"

namespace game {


	UpperArm::UpperArm(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, BossEnemy* origin, bool side)
		: GameObject(position, geom, shader, texture)
	{
		origin_ = origin;
		side_ = side;
		SetScale(1.5);
		switchTime_.Start(5);
		direction_ = false;
		if (side_) {
			SetPosition(glm::vec3(origin_->GetPosition().x - 2, origin_->GetPosition().y + 1, 0.0f));
		}
		else {
			SetPosition(glm::vec3(origin_->GetPosition().x + 2, origin_->GetPosition().y + 1, 0.0f));
			SetRotation(glm::pi<float>());
		}
	}


	void UpperArm::Update(double delta_time) {

		
		if (switchTime_.Finished()) {
			direction_ = !direction_;
			switchTime_.Start(2);
		}
		
		if (direction_) {
			SetPosition(glm::vec3(GetPosition().x, origin_->GetPosition().y + 0.1, 0.0f));
		}
		else {
			SetPosition(glm::vec3(GetPosition().x, origin_->GetPosition().y - 0.1, 0.0f));
		}
	}

} // namespace game