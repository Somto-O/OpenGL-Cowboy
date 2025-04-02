#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include <iostream>

#include "game_object.h"

namespace game {

	enum class EnemyType {
		BOSS,
		BANDIT,
		MOLE
	};

	class EnemyGameObject : public GameObject {
		public:
			EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, EnemyType type);

			// virtual update function, overridden by derived enemies
			virtual void Update(double delta_time) override;

			// getter
			EnemyType GetType() const { return type_; }

		protected:
			int health_ = 0;
			EnemyType type_;

	};
} // namespace game
#endif //ENEMY_GAME_OBJECT_H_
