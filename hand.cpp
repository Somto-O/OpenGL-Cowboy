#include <glm/gtc/constants.hpp>

#include "hand.h"

namespace game {


	Hand::Hand(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture,LowerArm* origin)
		: GameObject(position, geom, shader, texture)
	{
		SetScale(1.5);
		origin_ = origin;
		side_ = origin_->getSide();
		explosionReady_.Start(1);

	}


	void Hand::Update(double delta_time) {


		if (side_) {
			SetPosition(glm::vec3(origin_->GetPosition().x - 1, origin_->GetPosition().y, 0.0f));
		}
		else {
			SetPosition(glm::vec3(origin_->GetPosition().x + 1, origin_->GetPosition().y, 0.0f));
			SetRotation(glm::pi<float>());
		}
		

	}

} // namespace game