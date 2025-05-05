#include <glm/gtc/constants.hpp>

#include "LowerArm.h"

namespace game {


	LowerArm::LowerArm(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, UpperArm* origin)
		: GameObject(position, geom, shader, texture)
	{
		origin_ = origin;
		SetScale(1.5);
		side_ = origin_->getSide();
	}


	void LowerArm::Update(double delta_time) {

		
		if (side_) {
			SetPosition(glm::vec3(origin_->GetPosition().x - 1, origin_->GetPosition().y, 0.0f));
			
		}
		else {
			SetPosition(glm::vec3(origin_->GetPosition().x + 1, origin_->GetPosition().y, 0.0f));
			SetRotation(glm::pi<float>());
		}

		// Special collectible updates go here
	}

} // namespace game