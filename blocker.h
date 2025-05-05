#ifndef BLOCKER_H_
#define BLOCKER_H_

#include <iostream>


#include "player_game_object.h"
//#include "timer.h" - will include if needed

namespace game {

	class Blocker : public GameObject
	{
	public:
		Blocker(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player);

		// Update function for any special collectible object updates
		void Update(double delta_time) override;
		int getHealth()const { return health_; }
		void TakeDamage() { health_--; }

	private:
		PlayerGameObject* player_;
		int health_ = 3;
	};
} // namespace game

#endif //COLLECTIBLE_GAME_OBJECT_H_
