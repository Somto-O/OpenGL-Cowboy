#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>
#include <path_config.h>
#include "healthBar.h"
#include "sprite.h"
#include "shader.h"
#include "game.h"
#include "GunUi.h"
#include "text_game_object.h"
#include "timer.h"
#include "sherrifStar.h"
#include "heart.h"
#include "shield.h"
#include "blocker.h"
#include "bandit_enemy.h"
#include "particles.h"
#include "particle_system.h"
#include "UpperArm.h"
#include "LowerArm.h"
#include "Hand.h"
#include "Tnt.h"



namespace game {

	// Some configuration constants
	// They are written here as global variables, but ideally they should be loaded from a configuration file

	// Globals that define the OpenGL window and viewport
	const char* window_title_g = "Cowboy Rushdown"; // changed the window title from "Game Demo" to "Cowboy Rushdown"
	const unsigned int window_width_g = 1000;
	const unsigned int window_height_g = 2000;
	const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);

	// Directory with game resources such as textures
	const std::string resources_directory_g = RESOURCES_DIRECTORY;

	HealthBar* bar = nullptr;
	GunUi* guns = nullptr;

	void Game::SetupGameWorld(void)
	{

		// Setup the game world

		// **** Load all the textures that we will need
		//
		// The Textures enum is defined in public/game.h
		// and these are the corresponidng placeholders to avoid error msgs in the editor
		std::vector<std::string> textures;
		textures.push_back("/textures/cowboy2.png"); // tex_cowboy
		textures.push_back("/textures/Bandit.png"); // tex_bandit
		textures.push_back("/textures/item.png"); // tex_item
		textures.push_back("/textures/pistol.png"); // tex_pistol
		textures.push_back("/textures/shotgun.png"); // tex_shotgun
		textures.push_back("/textures/bullet.png"); // tex_bullet
		textures.push_back("/textures/shell.png"); // tex_shell
		textures.push_back("/textures/ammobox.png"); // tex_ammo
		textures.push_back("/textures/wildwest.png"); // tex_wildwest
		textures.push_back("/textures/healthBar.png"); // tex_healthbar
		textures.push_back("/textures/font.png"); // tex_font
		textures.push_back("/textures/SherrifStar.png"); // tex_star
		textures.push_back("/textures/Heart.png"); // tex_heart
		textures.push_back("/textures/Shield.png"); // tex_shield
		textures.push_back("/textures/blocker.png"); // tex_blocker
		textures.push_back("/textures/mole.png"); // tex_mole
		textures.push_back("/textures/boss.png"); // tex_boss
		textures.push_back("/textures/Hand.png"); // tex_hand
		textures.push_back("/textures/LowerArm.png"); // tex_lower
		textures.push_back("/textures/UpperArm.png"); // tex_upper
		textures.push_back("/textures/Tnt.png"); // tex_upper
		// Load textures
		LoadTextures(textures);

		// **** Setup all the game objects in the world

		// Setup the player object (position, texture, vertex count)
		// Note that, in this specific implementation, the player object should always be the first object in the game object vector 
		PlayerGameObject* player = new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_cowboy]);
		game_objects_.push_back(player);
		float pi_over_two = glm::pi<float>() / 2.0f;
		game_objects_[0]->SetRotation(pi_over_two);

		// Setup other objects
		game_objects_.push_back(new BanditEnemy(glm::vec3(-1.0f, 1.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_bandit], player));
		game_objects_[1]->SetRotation(pi_over_two);
		//game_objects_.push_back(new CollectibleGameObject(glm::vec3(1.0f, -0.5f, 0.0f), sprite_, &sprite_shader_, tex_[tex_ammo]));
		//game_objects_[2]->SetRotation(0.0f);

		// Health bar UI Crap
		guns = new GunUi(glm::vec3(1.0f, -0.5f, 0.0f), sprite_, &sprite_shader_, tex_[tex_pistol], tex_[tex_shotgun]);
		TextGameObject* text = new TextGameObject(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &text_shader_, tex_[tex_font]);
		TextGameObject* score = new TextGameObject(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &text_shader_, tex_[tex_font]);
		TextGameObject* time = new TextGameObject(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &text_shader_, tex_[tex_font]);
		TextGameObject* scoreword = new TextGameObject(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &text_shader_, tex_[tex_font]);
		bar = new HealthBar(glm::vec3(1.0f, -0.5f, 0.0f), sprite_, &sprite_shader_, tex_[tex_healthBar], guns, text, player, score, scoreword,time);
		game_objects_.push_back(guns);
		game_objects_.push_back(text);
		game_objects_.push_back(score);
		game_objects_.push_back(scoreword);
		game_objects_.push_back(time);
		game_objects_.push_back(bar);
		game_objects_.push_back(new SherrifStar(glm::vec3(1.0f, 2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_star]));
		game_objects_.push_back(new Heart(glm::vec3(-2.0f, 3.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_heart]));
		game_objects_.push_back(new Shield(glm::vec3(-1.0f, 3.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_shield]));

		
		

		// Setup background
		// In this specific implementation, the background is always the
		// last object
		GameObject* background = new GameObject(glm::vec3(0.0f, 0.0f, 1.0f), sprite_, &background_shader_, tex_[tex_wildwest]);
		background->SetScale(12.0);
		game_objects_.push_back(background);

		// Initialize score
		Score = 0;

		// Initialize timers
		mole_spawn_timer_.Start(2.0f);
		bandit_spawn_timer_.Start(10.0f);
		heart_spawn_timer_.Start(5.0f);
	}


	void Game::DestroyGameWorld(void)
	{
		// Free memory for all objects
		// Only need to delete objects that are not automatically freed
		for (int i = 0; i < game_objects_.size(); i++) {
			delete game_objects_[i];
		}
	}


	void Game::HandleControls(double delta_time)
	{
		// If the game is over, ignore control input.
		if (game_over_)
			return;

		// Get player game object

		PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);

		// Get current position and angle
		glm::vec3 curpos = player->GetPosition();
		float angle = player->GetRotation();
		// Compute current bearing direction
		glm::vec3 dir = player->GetBearing();
		glm::vec3 right = player->GetRight();
		// Adjust motion increment and angle increment 
		// if translation or rotation is too slow
		float speed = delta_time * 500.0;
		float motion_increment = 0.005 * speed;
		float angle_increment = (glm::pi<float>() / 1800.0f) * speed;

		// Accumulate movement changes
		glm::vec3 movement(0.0f);

		if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
			movement += motion_increment * dir;
		}
		if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
			movement -= motion_increment * dir;
		}
		if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
			movement -= motion_increment * right;
		}
		if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
			movement += motion_increment * right;
		}
		// Apply accumulated movement
		player->SetPosition(curpos + movement);
		
		if (glfwGetKey(window_, GLFW_KEY_R) == GLFW_PRESS) {
			// reload weapon
		}
		if (glfwGetKey(window_, GLFW_KEY_P) == GLFW_PRESS) {
			if (!p_key_pressed_) {
				guns->gunSwap();
				// Toggle between pistol and shotgun
				if (current_projectile_state_ == ProjectileState::PISTOL) {
					std::cout << "Gun: shotgun" << std::endl;
					current_projectile_state_ = ProjectileState::SHOTGUN;
				}
				else {
					current_projectile_state_ = ProjectileState::PISTOL;
					std::cout << "Gun: pistol" << std::endl;
				}
				p_key_pressed_ = true;
			}

		}
		else {
			p_key_pressed_ = false;
		}
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) { // shoot weapon
			if (player->bulletcooldown_.Finished()) {

				// Get current position and direction
				glm::vec3 player_position = player->GetPosition();
				float player_angle = player->GetRotation();

				GLuint projectile_texture = (current_projectile_state_ == ProjectileState::PISTOL) ? tex_[tex_bullet] : tex_[tex_shell];

				if (current_projectile_state_ == ProjectileState::PISTOL) {
					// Check if the player has enough ammo
					if (pistol_ammo_ > 0) {
						pistol_ammo_--;
					}
					else {
						//std::cout << "Pistol out of ammo!" << std::endl;
						return;
					}

					// Create a new projectile at the player's position with the player's angle
					ProjectileGameObject* projectile = new ProjectileGameObject(player_position, sprite_, &sprite_shader_, projectile_texture, 3.0f, player_angle, current_projectile_state_, player);

					game_objects_.insert(game_objects_.end() - 1, projectile);

					player->bulletcooldown_.Start(player->getPistolReloadSpeed());
				}
				else {
					// Check if the player has enough ammo
					if (shotgun_ammo_ > 0) {
						shotgun_ammo_--;
					}
					else {
						//std::cout << "Shotgun out of ammo!" << std::endl;
						return;
					}

					// Create three projectiles with 5 degrees spread
					float spread_angle = glm::radians(5.0f);
					for (int i = -1; i <= 1; ++i)
					{
						float angle_offset = i * spread_angle;
						ProjectileGameObject* projectile = new ProjectileGameObject(player_position, sprite_, &sprite_shader_, projectile_texture, 3.0f, player_angle + angle_offset, current_projectile_state_, player);
						game_objects_.insert(game_objects_.end() - 1, projectile);
					}
					player->bulletcooldown_.Start(player->getShotGunReloadSpeed());
				}
			}
		}
		else {
			space_key_pressed_ = false; // Reset the flag when space is released
		}
	}


	void Game::Update(double delta_time)
	{
		PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);

		// Check if the player's health is 0 and set game_over_ to true and stop and delete all enemies and their projectiles
		if (player->getHealth() <= 0 && !game_over_) {
			game_over_ = true;
			std::cout << "Game Over! Closing in 2 seconds..." << std::endl;
			glfwSetTime(0);
			for (int i = 1; i < game_objects_.size(); i++) {
				if (dynamic_cast<EnemyGameObject*>(game_objects_[i]) || dynamic_cast<ProjectileGameObject*>(game_objects_[i])) {
					delete game_objects_[i];
					game_objects_.erase(game_objects_.begin() + i);
					i--;
				}
			}
		}

		// If game_over_ is true, wait 2 seconds before closing the game
		if (game_over_ && glfwGetTime() >= 2.0) {
			glfwSetWindowShouldClose(window_, GLFW_TRUE);
			return;
		}


		// Update all game objects
		for (int i = 0; i < game_objects_.size(); i++) {

			GameObject* current_game_object = game_objects_[i];
			current_game_object->Update(delta_time);

			// projectile-enemy collision
			if (dynamic_cast<ProjectileGameObject*>(current_game_object)) {
				ProjectileGameObject* projectile = dynamic_cast<ProjectileGameObject*>(current_game_object);
				for (int j = 0; j < game_objects_.size() - 1; ++j) {
					if (i == j) continue;

					GameObject* other_game_object = game_objects_[j];
					if (dynamic_cast<EnemyGameObject*>(other_game_object) && projectile->getOwner() == player) {
						EnemyGameObject* bad = dynamic_cast<EnemyGameObject*>(other_game_object);
						// Check for collision
						//glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
						//glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
						//float enemy_radius = other_game_object->GetScale();
						//RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)
						float distance = glm::length(current_game_object->GetPosition() - other_game_object->GetPosition());
						if (distance < bad->getFat()) {
							// Handle collision
							HandleCollision(current_game_object, other_game_object);
						}
					}
					else if (dynamic_cast<PlayerGameObject*>(other_game_object) && projectile->getOwner() != player) {
						// Check for collision
						glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
						glm::vec2 player_position = glm::vec2(other_game_object->GetPosition());
						float player_radius = other_game_object->GetScale() * 0.4f;

						if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), player_position, player_radius)) {
							// Handle collision with player
							PlayerGameObject* player_obj = dynamic_cast<PlayerGameObject*>(other_game_object);
							if (player_obj) {
								player_obj->TakeDamage();
								delete current_game_object; // Remove the projectile
								game_objects_.erase(game_objects_.begin() + i);
								i--;
							}
						}
					}
				}
			}
			// player-collectible collision
			else if (dynamic_cast<CollectibleGameObject*>(current_game_object)) {
				if (dynamic_cast<SherrifStar*>(current_game_object)) {

					for (int j = 0; j < game_objects_.size() - 1; ++j) {
						if (i == j) continue;

						GameObject* other_game_object = game_objects_[j];
						if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
							// Check for collision
							glm::vec2 collectible_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 player_position = glm::vec2(other_game_object->GetPosition());
							float player_radius = other_game_object->GetScale() * 0.3f;

							if (RayCircleCollision(collectible_position, collectible_position + glm::vec2(current_game_object->GetBearing()), player_position, player_radius)) {
								// Handle collision
								player->powerUP_.Start(5);
								delete current_game_object;
								game_objects_.erase(game_objects_.begin() + i);
								i--;

							}
						}
					}
				}
				else if (dynamic_cast<Heart*>(current_game_object)) {

					for (int j = 0; j < game_objects_.size() - 1; ++j) {
						if (i == j) continue;

						GameObject* other_game_object = game_objects_[j];
						if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
							// Check for collision
							glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
							float enemy_radius = other_game_object->GetScale() * 0.5f;

							if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)) {
								// Handle collision
								player->AddHealth();

								delete current_game_object;
								game_objects_.erase(game_objects_.begin() + i);
								i--;

							}
						}
					}

				}
				else if (dynamic_cast<Shield*>(current_game_object)) {

					for (int j = 0; j < game_objects_.size() - 1; ++j) {
						if (i == j) continue;

						GameObject* other_game_object = game_objects_[j];
						if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
							// Check for collision
							glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
							float enemy_radius = other_game_object->GetScale() * 0.3;

							if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)) {
								// Handle collision
								if (!player->getBlocking())
									game_objects_.push_back(new Blocker(glm::vec3(-1.0f, 3.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_blocker], player));
								player->Block();
								delete current_game_object;
								game_objects_.erase(game_objects_.begin() + i);
								i--;

							}
						}
					}

				}
				// ammo collision
				else if (dynamic_cast<CollectibleGameObject*>(current_game_object)) {
					CollectibleGameObject* collectible = dynamic_cast<CollectibleGameObject*>(current_game_object);
					for (int j = 0; j < game_objects_.size() - 1; ++j) {
						if (i == j) continue;
						GameObject* other_game_object = game_objects_[j];
						if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
							// Check for collision
							glm::vec2 collectible_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 player_position = glm::vec2(other_game_object->GetPosition());
							float player_radius = other_game_object->GetScale() * 0.5f;
							if (RayCircleCollision(collectible_position, collectible_position + glm::vec2(current_game_object->GetBearing()), player_position, player_radius)) {
								if (current_projectile_state_ == ProjectileState::PISTOL)
								{
									pistol_ammo_ = 10;
								}
								else
								{
									shotgun_ammo_ = 7;
								}
								delete current_game_object;
								game_objects_.erase(game_objects_.begin() + i);
								i--;

							}
						}
					}
				}

			}
			// enemy projectile-blocker collision
			else if (dynamic_cast<Blocker*>(current_game_object)) {
				Blocker* Blockage = dynamic_cast<Blocker*>(current_game_object);
				for (int j = 0; j < game_objects_.size() - 1; ++j) {
					if (i == j) continue;

					GameObject* other_game_object = game_objects_[j];
					if (dynamic_cast<ProjectileGameObject*>(other_game_object)) {
						ProjectileGameObject* bullet = dynamic_cast<ProjectileGameObject*>(other_game_object);
						if (!(bullet->getOwner() == player)) {

							// Check for collision
							glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
							float enemy_radius = other_game_object->GetScale();

							if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)) {
								Blockage->TakeDamage();
								bullet->setOwner(player);
								bullet->SetAngle(-(bullet->getAngle()));
								if (Blockage->getHealth() <= 0) {
									player->SetBlocking(false);
									delete current_game_object;
									game_objects_.erase(game_objects_.begin() + i);
									i--;
								}
							}
						}
					}
					else if (dynamic_cast<Tnt*>(other_game_object)) {
						Tnt* bullet = dynamic_cast<Tnt*>(other_game_object);
						

							// Check for collision
							glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
							float enemy_radius = other_game_object->GetScale();

							if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)) {
								Blockage->TakeDamage();
								
								bullet->SetRotation(-(bullet->GetRotation()));
								if (Blockage->getHealth() <= 0) {
									player->SetBlocking(false);
									delete current_game_object;
									game_objects_.erase(game_objects_.begin() + i);
									i--;
								}
							}
						
					}
				}
			}
			// player-mole collision
			else if (dynamic_cast<MoleEnemy*>(current_game_object)) {
				EnemyGameObject* mole = dynamic_cast<EnemyGameObject*>(current_game_object);
				if (mole->GetType() == EnemyType::MOLE) {
					for (int j = 0; j < game_objects_.size() - 1; ++j) {
						if (i == j) continue;

						GameObject* other_game_object = game_objects_[j];
						if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
							// Check for collision
							glm::vec2 mole_position = glm::vec2(current_game_object->GetPosition());
							glm::vec2 player_position = glm::vec2(other_game_object->GetPosition());
							float player_radius = other_game_object->GetScale() * 0.1f;

							if (RayCircleCollision(mole_position, mole_position + glm::vec2(current_game_object->GetBearing()), player_position, player_radius)) {
								// Handle collision
								PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(other_game_object);
								if (player) {
									player->TakeDamage(); // Reduce player's health by 1
									delete current_game_object; // Remove the mole
									game_objects_.erase(game_objects_.begin() + i);
									i--;
								}
							}
						}
					}
				}
			}
			else if (dynamic_cast<Tnt*>(current_game_object)) {

				for (int j = 0; j < game_objects_.size() - 1; ++j) {
					if (i == j) continue;

					GameObject* other_game_object = game_objects_[j];
					if (dynamic_cast<PlayerGameObject*>(other_game_object)) {
						// Check for collision
						glm::vec2 projectile_position = glm::vec2(current_game_object->GetPosition());
						glm::vec2 enemy_position = glm::vec2(other_game_object->GetPosition());
						float enemy_radius = other_game_object->GetScale();

						if (RayCircleCollision(projectile_position, projectile_position + glm::vec2(current_game_object->GetBearing()), enemy_position, enemy_radius)) {
							// Handle collision
							
								
							player->TakeDamage();
							delete current_game_object;
							game_objects_.erase(game_objects_.begin() + i);
							i--;

						}
					}
				}

			}

			// This is not collision this Controls the enemies shooting
			else if (dynamic_cast<EnemyGameObject*>(current_game_object)) {
				EnemyGameObject* Badguy = dynamic_cast<EnemyGameObject*>(current_game_object);
				if (Badguy->GetType() == EnemyType::BANDIT && Badguy->attackTime_.Finished()) {
					ProjectileGameObject* projectile = new ProjectileGameObject(Badguy->GetPosition(), sprite_, &sprite_shader_, tex_[tex_bullet], 3.0f, Badguy->GetRotation(), current_projectile_state_, current_game_object);
					game_objects_.push_back(projectile);
					Badguy->attackTime_.Start(1.5);

				}
			}
			else if (dynamic_cast<Hand*>(current_game_object)) {
				Hand* hand = dynamic_cast<Hand*>(current_game_object);
				if (hand->explosionReady_.Finished()) {

					Tnt* projectile = new Tnt(glm::vec3(hand->GetPosition().x, hand->GetPosition().y, -1.0f), sprite_, &sprite_shader_, tex_[tex_tnt], player);
					game_objects_.push_back(projectile);
					hand->explosionReady_.Start(1.3);

				}
			}
		}

		// Spawn enemies
		if (Score < 5) {
			glm::vec3 player_position = player->GetPosition();

			float x = static_cast<float>(rand() % 8 - 4);
			float y = static_cast<float>(rand() % 14 - 7);

			// Add the player's position to the random offset
			glm::vec3 spawn_position = player_position + glm::vec3(x, y, 0.0f);

			if (mole_spawn_timer_.Finished()) {
				game_objects_.insert(game_objects_.end() - 1, enemy_factory_.CreateEnemy(EnemyType::MOLE, spawn_position, sprite_, &sprite_shader_, tex_[tex_mole], player));
				mole_spawn_timer_.Start(5.0f);
			}
			if (bandit_spawn_timer_.Finished()) {
				game_objects_.insert(game_objects_.end() - 1, enemy_factory_.CreateEnemy(EnemyType::BANDIT, spawn_position, sprite_, &sprite_shader_, tex_[tex_bandit], player));
				bandit_spawn_timer_.Start(10.0f);
			}
		}
		// spawn boss
		else if (Score == 5) {
			BossEnemy* boss = new BossEnemy(glm::vec3(0.3f, 2.0f, 1.0f), sprite_, &sprite_shader_, tex_[tex_boss], player);
			game_objects_.push_back(boss);

			UpperArm* rightU = new UpperArm(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_upper], boss, true);
			UpperArm* leftU = new UpperArm(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_upper], boss, false);

			LowerArm* rightL = new LowerArm(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_lower], rightU);
			LowerArm* leftL = new LowerArm(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_lower], leftU);

			Hand* rightH = new Hand(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_hand], rightL);
			Hand* leftH = new Hand(glm::vec3(0.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_hand], leftL);

			game_objects_.push_back(rightH);
			game_objects_.push_back(leftH);
			game_objects_.push_back(rightU);
			game_objects_.push_back(leftU);
			game_objects_.push_back(rightL);
			game_objects_.push_back(leftL);		
			
			Score++; // Increment score to prevent multiple boss spawns
			player->addScore();
			std::cout << "Score: " << Score << std::endl;
		}

		// Spawn hearts and ammo
		if (heart_spawn_timer_.Finished()) {
			glm::vec3 player_position = player->GetPosition();

			// Generate a random position
			float x = static_cast<float>(rand() % 8 - 4);
			float y = static_cast<float>(rand() % 14 - 7);

			// Add the player's position to the random offset
			glm::vec3 spawn_position = player_position + glm::vec3(x, y, 0.0f);

			// Spawn a Heart collectible
			game_objects_.push_back(new Heart(spawn_position, sprite_, &sprite_shader_, tex_[tex_heart]));

			// Restart the timer
			heart_spawn_timer_.Start(5.0f);
		}

		if (ammo_spawn_timer_.Finished()) {
			glm::vec3 player_position = player->GetPosition();

			// Generate a random offset
			float x = static_cast<float>(rand() % 8 - 4);
			float y = static_cast<float>(rand() % 14 - 7);

			// Add the player's position to the random offset
			glm::vec3 spawn_position = player_position + glm::vec3(x, y, 0.0f);

			// Spawn an ammo collectible
			game_objects_.push_back(new CollectibleGameObject(spawn_position, sprite_, &sprite_shader_, tex_[tex_ammo]));

			// Restart the timer
			ammo_spawn_timer_.Start(3.0f);
		}
	}


	void Game::Render(void) {
		PlayerGameObject* player_ = dynamic_cast<PlayerGameObject*>(game_objects_[0]);
		// Clear background
		glClearColor(viewport_background_color_g.r,
			viewport_background_color_g.g,
			viewport_background_color_g.b, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use aspect ratio to properly scale the window
		int width, height;
		glfwGetWindowSize(window_, &width, &height);
		glm::mat4 window_scale_matrix;
		if (width > height) {
			float aspect_ratio = ((float)width) / ((float)height);
			window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / aspect_ratio, 1.0f, 1.0f));
		}
		else {
			float aspect_ratio = ((float)height) / ((float)width);
			window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f / aspect_ratio, 1.0f));
		}

		// Set view to zoom out, centered by default at 0,0
		float camera_zoom = 0.25f;
		glm::mat4 camera_move_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(player_->GetPosition().x), -(player_->GetPosition().y), 0));
		glm::mat4 camera_zoom_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));
		glm::mat4 view_matrix = window_scale_matrix * camera_zoom_matrix * camera_move_matrix;
		glm::vec3 idea = glm::vec3(view_matrix[3]);
		bar->SetPosition(glm::vec3(player_->GetPosition().x + 2.7, player_->GetPosition().y - 4, 0.0f));





		// Render all game objects
		for (int i = 0; i < game_objects_.size(); i++) {
			game_objects_[i]->Render(view_matrix, current_time_);
		}
	}


	void Game::MainLoop(void)
	{
		// Loop while the user did not close the window
		double last_time = glfwGetTime();
		while (!glfwWindowShouldClose(window_)) {

			// Calculate delta time
			double current_time = glfwGetTime();
			double delta_time = current_time - last_time;
			last_time = current_time;

			// Update window events like input handling
			glfwPollEvents();

			// Handle user input
			HandleControls(delta_time);

			// Update all the game objects
			Update(delta_time);

			// Render all the game objects
			Render();

			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window_);
		}
	}


	Game::Game(void) : space_key_pressed_(false), current_projectile_state_(ProjectileState::PISTOL), p_key_pressed_(false)
	{
		// Don't do work in the constructor, leave it for the Init() function
	}


	void Game::Init(void)
	{

		// Initialize the window management library (GLFW)
		if (!glfwInit()) {
			throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
		}

		// Set whether window can be resized
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		// Create a window and its OpenGL context
		window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
		if (!window_) {
			glfwTerminate();
			throw(std::runtime_error(std::string("Could not create window")));
		}

		// Make the window's OpenGL context the current one
		glfwMakeContextCurrent(window_);

		// Initialize the GLEW library to access OpenGL extensions
		// Need to do it after initializing an OpenGL context
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char*)glewGetErrorString(err))));
		}

		// Set event callbacks
		glfwSetFramebufferSizeCallback(window_, ResizeCallback);

		// Initialize sprite geometry
		sprite_ = new Sprite();
		sprite_->CreateGeometry();

		// Initialize sprite shader
		sprite_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/sprite_fragment_shader.glsl")).c_str());
		text_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/text_fragment_shader.glsl")).c_str());
		background_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader_2.glsl")).c_str(), (resources_directory_g + std::string("/sprite_background_shader.glsl")).c_str());
		particle_shader_.Init((resources_directory_g + std::string("/particle_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/particle_fragment_shader.glsl")).c_str());
		// Initialize time
		current_time_ = 0.0;

		// initialize space key pressed
		space_key_pressed_ = false;
	}


	Game::~Game()
	{
		// Free memory used by game world
		DestroyGameWorld();

		// Free rendering resources
		delete sprite_;

		// Close window
		glfwDestroyWindow(window_);
		glfwTerminate();
	}


	void Game::ResizeCallback(GLFWwindow* window, int width, int height)
	{
		// Set OpenGL viewport based on framebuffer width and height
		glViewport(0, 0, width, height);
	}


	void Game::SetTexture(GLuint w, const char* fname)
	{
		// Bind texture buffer
		glBindTexture(GL_TEXTURE_2D, w);

		// Load texture from a file to the buffer
		int width, height;
		unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
		if (!image) {
			std::cout << "Cannot load texture " << fname << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		// Texture Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Texture Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T, GL_REPEAT);
	}


	void Game::LoadTextures(std::vector<std::string>& textures)
	{
		// Allocate a buffer for all texture references
		int num_textures = textures.size();
		tex_ = new GLuint[num_textures];
		glGenTextures(num_textures, tex_);
		// Load each texture
		for (int i = 0; i < num_textures; i++) {
			SetTexture(tex_[i], (resources_directory_g + textures[i]).c_str());
		}
		// Set first texture in the array as default
		glBindTexture(GL_TEXTURE_2D, tex_[0]);
	}


	// function to handle the collisions
	void Game::HandleCollision(GameObject* obj1, GameObject* obj2) {
		PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(game_objects_[0]);
		// Remove the projectile from the game
		std::cout << "Projectile hit enemy!" << std::endl;
		auto it = std::find(game_objects_.begin(), game_objects_.end(), obj1);
		if (it != game_objects_.end()) {
			delete* it;
			game_objects_.erase(it);
		}

		// Handle enemy hit logic
		EnemyGameObject* enemy_obj = dynamic_cast<EnemyGameObject*>(obj2);
		if (enemy_obj) {
			glm::vec3 enemy_position = enemy_obj->GetPosition();
			enemy_obj->TakeDamage(1);
			if (enemy_obj->IsDestroyed()) {
				auto it = std::find(game_objects_.begin(), game_objects_.end(), obj2);
				if (it != game_objects_.end()) {
					delete* it;
					game_objects_.erase(it);
				}

				Score++; // Increment score when an enemy is destroyed
				player->addScore();
				std::cout << "Score: " << Score << std::endl;
				
				// Spawn a collectible item
				if (Score % 2 == 0) {
					// Drop a Shield collectible
					game_objects_.push_back(new Shield(enemy_position, sprite_, &sprite_shader_, tex_[tex_shield]));
				}
				if (Score % 3 == 0) {
					// Drop a SherrifStar collectible
					game_objects_.push_back(new SherrifStar(enemy_position, sprite_, &sprite_shader_, tex_[tex_star]));
				}

			}
		}
	}


	bool Game::RayCircleCollision(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& center, float radius)
	{
		// direction vector, d
		glm::vec2 d = p1 - p0;
		// vector from p0 to center
		glm::vec2 f = p0 - center;

		// coefficients for the quadratic equation
		float a = glm::dot(d, d);
		float b = 2.0f * glm::dot(f, d);
		float c = glm::dot(f, f) - radius * radius;
		// discriminant
		float discriminant = b * b - 4.0f * a * c;

		// if discriminant is negative, no intersection
		if (discriminant < 0) {
			return false;
		}
		else { // if discriminant is positive, there are two solutions
			discriminant = sqrt(discriminant);
			float t1 = (-b - discriminant) / (2.0f * a);
			float t2 = (-b + discriminant) / (2.0f * a);
			// if t1 or t2 is between 0 and 1, there is an intersection
			if ((t1 >= 0.0f && t1 <= 1.0f) || (t2 >= 0.0f && t2 <= 1.0f)) {
				return true;
			}
		}

		return false;
	}

} // namespace game
