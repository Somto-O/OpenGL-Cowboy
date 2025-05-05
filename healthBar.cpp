#include <glm/gtc/constants.hpp>

#include "healthBar.h"

namespace game {

	HealthBar::HealthBar(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GunUi* guns, TextGameObject* t,PlayerGameObject* p ,TextGameObject* s, TextGameObject* SCORE, TextGameObject* Time)
		: GameObject(position, geom, shader, texture)
	
	{

		SetScale(2.5);
		Start = glfwGetTime();
		ScoreWord = SCORE;
		healthpoints = t;
		t->SetScale(0.5);
		scorepoints = s;
		s->SetScale(0.7);
		Time_ = Time;

		player = p;

		gunPic = guns;
		gunPic->SetScale(0.5);
	}


	void HealthBar::Update(double delta_time)
	{
		gunPic->SetPosition(glm::vec3(position_.x, position_.y-0.6, -1.0f));
		healthpoints->SetPosition(glm::vec3(position_.x+0.5, position_.y+0.1, -1.0f));
		scorepoints->SetPosition(glm::vec3(position_.x+0.3, position_.y - 1.25, -1.0f));
		ScoreWord->SetPosition(glm::vec3(position_.x-0.5 , position_.y - 1.4, -1.0f));
		healthpoints->SetText(std::to_string(player->getHealth()));
		scorepoints->SetText(std::to_string(player->getScore()));
		ScoreWord->SetText("SCORE: ");
		Time_->SetText(std::to_string((glfwGetTime() - Start)));
		Time_->SetPosition(glm::vec3(position_.x - 6, position_.y + 9.0, -1.0f));
	}

} // namespace game


