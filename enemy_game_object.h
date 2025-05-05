#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include <iostream>

#include "game_object.h"
#include "Timer.h"
#include "player_game_object.h"

namespace game {

	enum class EnemyType {
		BOSS,
		BANDIT,
		MOLE
	};

	class EnemyGameObject : public GameObject {
		public:
			EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, EnemyType type, PlayerGameObject* player);

			// virtual update function, overridden by derived enemies
			virtual void Update(double delta_time) override;

			// getter
			EnemyType GetType() const { return type_; }

			// other enemy-specific methods can be added here
			void TakeDamage(int);

			bool IsDestroyed() const;

			float getFat()const { return fatness; }

			Timer attackTime_;

		protected:
			int health_;
			EnemyType type_;
			PlayerGameObject* player_;
			float fatness;

	};
} // namespace game
#endif //ENEMY_GAME_OBJECT_H_
