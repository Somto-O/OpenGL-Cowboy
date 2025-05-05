#ifndef TNT_H_
#define TNT_H_

#include <iostream>


#include "game_object.h"
#include "player_game_object.h"


namespace game {

	class Tnt : public GameObject
	{
	public:
		Tnt(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, PlayerGameObject* player);



		// Update function for any special collectible object updates
		void Update(double delta_time) override;
		

	private:
		glm::vec3 dir_;
		glm::vec3 target_;
		glm::vec3 velo_;
		

	};
} // namespace game

#endif 