#include <glm/gtc/constants.hpp>

#include "gunUi.h"

namespace game {

	GunUi::GunUi(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint gunOne, GLuint gunTwo)
		: GameObject(position, geom, shader, gunOne)

	{
		FirstGun = gunOne;
		SecondGun = gunTwo;
	}

	void GunUi :: gunSwap() {
		if (texture_ == SecondGun) {
			texture_ = FirstGun;
			return;
		}
		if (texture_ == FirstGun) {
			texture_ = SecondGun;
			return;
		}
	}


	void GunUi::Update(double delta_time)
	{
		// Special enemy updates go here
	}

} // namespace game


