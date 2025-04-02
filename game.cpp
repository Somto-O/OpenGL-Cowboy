#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>
#include <path_config.h>

#include "sprite.h"
#include "shader.h"
#include "game.h"

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


	void Game::SetupGameWorld(void)
	{

		// Setup the game world

		// **** Load all the textures that we will need
		//
		// The Textures enum is defined in public/game.h
		// and these are the corresponidng placeholders to avoid error msgs in the editor
		std::vector<std::string> textures;
		textures.push_back("/textures/cowboy.png"); // tex_cowboy
		textures.push_back("/textures/boss.png"); // tex_boss
		textures.push_back("/textures/item.png"); // tex_item
		textures.push_back("/textures/pistol.png"); // tex_pistol
		textures.push_back("/textures/shotgun.png"); // tex_shotgun
		textures.push_back("/textures/bullet.png"); // tex_bullet
		textures.push_back("/textures/wildwest.png"); // tex_wildwest
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
		game_objects_.push_back(new EnemyGameObject(glm::vec3(-1.0f, 1.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_boss], EnemyType::BOSS));
		game_objects_[1]->SetRotation(pi_over_two);
		game_objects_.push_back(new CollectibleGameObject(glm::vec3(1.0f, -0.5f, 0.0f), sprite_, &sprite_shader_, tex_[tex_item]));
		game_objects_[2]->SetRotation(pi_over_two);

		// Setup background
		// In this specific implementation, the background is always the
		// last object
		GameObject* background = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[tex_wildwest]);
		background->SetScale(12.0);
		game_objects_.push_back(background);
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
		/* If the game is over, ignore control input.
		if (game_over_)
			return;
		*/

		// Get player game object
		GameObject* player = game_objects_[0];
		// Get current position and angle
		glm::vec3 curpos = player->GetPosition();
		float angle = player->GetRotation();
		// Compute current bearing direction
		glm::vec3 dir = player->GetBearing();
		// Adjust motion increment and angle increment 
		// if translation or rotation is too slow
		float speed = delta_time * 500.0;
		float motion_increment = 0.001 * speed;
		float angle_increment = (glm::pi<float>() / 1800.0f) * speed;

		// Check for player input and make changes accordingly
		if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
			player->SetPosition(curpos + motion_increment * dir);
		}
		if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
			player->SetPosition(curpos - motion_increment * dir);
		}
		if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
			player->SetRotation(angle - angle_increment);
		}
		if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
			player->SetRotation(angle + angle_increment);
		}
		if (glfwGetKey(window_, GLFW_KEY_Z) == GLFW_PRESS) {
			player->SetPosition(curpos - motion_increment * player->GetRight());
		}
		if (glfwGetKey(window_, GLFW_KEY_C) == GLFW_PRESS) {
			player->SetPosition(curpos + motion_increment * player->GetRight());
		}
		if (glfwGetKey(window_, GLFW_KEY_R) == GLFW_PRESS) {
			// reload weapon
		}
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
			// shoot weapon		
			GameObject* player = game_objects_[0];
			// Get current position and direction
			glm::vec3 player_position = player->GetPosition();
			float player_angle = player->GetRotation();

			// Create a new projectile at the player's position with the player's angle
			ProjectileGameObject* projectile = new ProjectileGameObject(player_position, sprite_, &sprite_shader_, tex_[tex_bullet], 1.0f, player_angle + (2.0f * glm::pi<float>()));

			// Add the projectile to the game objects vector
			game_objects_.insert(game_objects_.end() - 1, projectile);
		}
	}











	void Game::Update(double delta_time)
	{
		// Update all game objects
		for (int i = 0; i < game_objects_.size(); i++) {

			GameObject* current_game_object = game_objects_[i];
			current_game_object->Update(delta_time);

			// Where we would check collisions
			for (int j = i + 1; j < game_objects_.size() - 1; ++j) {
				GameObject* obj1 = current_game_object;
				GameObject* obj2 = game_objects_[j];

			}
		}
	}


	void Game::Render(void) {

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
		glm::mat4 camera_zoom_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));
		glm::mat4 view_matrix = window_scale_matrix * camera_zoom_matrix;

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


	Game::Game(void)
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

		// Initialize time
		current_time_ = 0.0;
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
	void Game::HandleCollision() {
		// placeholder for when we implement it
		return;
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
