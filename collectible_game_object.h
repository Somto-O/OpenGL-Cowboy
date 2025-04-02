#ifndef COLLECTIBLE_GAME_OBJECT_H_
#define COLLECTIBLE_GAME_OBJECT_H_

#include <iostream>

#include "game_object.h"
//#include "timer.h" - will include if needed

namespace game {

	class CollectibleGameObject : public GameObject 
	{
		public:
			CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

			// Update function for any special collectible object updates
			void Update(double delta_time) override;

		private:

	};
} // namespace game

#endif //COLLECTIBLE_GAME_OBJECT_H_
