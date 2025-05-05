#ifndef SHERRIF_STAR_H_
#define SHERRIF_STAR_H_

#include <iostream>

#include "collectible_game_object.h"


namespace game {

	class SherrifStar : public CollectibleGameObject
	{
	public:
		SherrifStar(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		float getNewTime() const{ return newTime; }

		// Update function for any special collectible object updates
		void Update(double delta_time) override;

	private:
		float newTime = 0.5;

	};
} // namespace game

#endif 