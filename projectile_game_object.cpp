#include "projectile_game_object.h"

namespace game {
	// Constructor
	ProjectileGameObject::ProjectileGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float speed, float angle)
		: GameObject(position, geom, shader, texture), speed_(speed), angle_(angle),
		state_(ProjectileState::PISTOL),
		pistol_texture_(texture),
		shotgun_texture_(texture),
		damage_(0),
		magazine_size_(0)
	{
		lifespan_.Start(3.0f);
		prev_pos_ = position;
	}

	// Update
	void ProjectileGameObject::Update(double delta_time)
	{
		// Store previous position before udating
		prev_pos_ = GetPosition();

		if (state_ == ProjectileState::PISTOL)
		{
			SetTexture(pistol_texture_);
			magazine_size_ = 6;
			damage_ = 1;

			// Get position and move in the direction of the angle
			glm::vec3 pos = GetPosition();
			pos.x += speed_ * cos(angle_) * static_cast<float>(delta_time);
			pos.y += speed_ * sin(angle_) * static_cast<float>(delta_time);
			SetPosition(pos);

			// rotate sprite correctly
			SetRotation(angle_);
		}
		else if (state_ == ProjectileState::SHOTGUN)
		{
			SetTexture(shotgun_texture_);
			magazine_size_ = 3;
			damage_ = 3;

			// triple shot implementation goes here


			// rotate sprites accordingly
			//SetRotation(angle_);
		}
	}

	bool ProjectileGameObject::IsExpired() const
	{
		return lifespan_.Finished();
	}

	void ProjectileGameObject::SetTexture(GLuint texture)
	{
		texture_ = texture;
	}

	void ProjectileGameObject::Reload(int mag_size)
	{
		magazine_size_ = mag_size;
	}

	void ProjectileGameObject::Shoot()
	{
		if (magazine_size_ > 0)
		{
			magazine_size_--;
			std::cout << "Ammo left: " << magazine_size_ << std::endl;
		}
		else
		{
			std::cout << "Out of ammo!" << std::endl;
		}
	}

} // namespace game