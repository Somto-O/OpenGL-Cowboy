#include <glm/gtc/constants.hpp>

#include "enemy_game_object.h"



namespace game {

	EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, EnemyType type, PlayerGameObject* player)
		: GameObject(position, geom, shader, texture),
		  type_(type),
		health_(0)
	{
		player_ = player;
	}


	void EnemyGameObject::Update(double delta_time)
	{
		SetRotation(-glm::pi<float>() / 2.0f);
		//SetPosition(glm::vec3(position_.x+1, position_.y, 0.0f));	
	}

	void EnemyGameObject::TakeDamage(int damage)
	{
		health_ -= damage;
		std::cout << "Enemy took " << damage << " damage! Health remaining: " << health_ << std::endl;
	}

	bool EnemyGameObject::IsDestroyed() const
	{
		return health_ <= 0;
	}

} // namespace game


