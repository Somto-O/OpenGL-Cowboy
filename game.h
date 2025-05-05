#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "shader.h"
#include "game_object.h"
#include "player_game_object.h"
#include "collectible_game_object.h"
#include "enemy_game_object.h"
#include "projectile_game_object.h"
#include "timer.h"
#include "enemy_factory.h"

namespace game {

    // A class for holding the main game objects
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();

            // Call Init() before calling any other method
            // Initialize graphics libraries and main window
            void Init(void); 

            // Textures enum
            enum Textures { // just as a placeholder
                tex_cowboy = 0,
                tex_bandit = 1,
                tex_item = 2,
                tex_pistol = 3,
                tex_shotgun = 4,
                tex_bullet = 5,
                tex_shell = 6,
                tex_ammo = 7,
                tex_wildwest = 8,
                tex_healthBar = 9,
                tex_font = 10,
                tex_star = 11,
                tex_heart = 12,
                tex_shield = 13,
                tex_blocker = 14,
                tex_mole = 15,
                tex_boss = 16,
                tex_hand = 17,
                tex_lower = 18,
                tex_upper = 19,
                tex_tnt = 20
            };

            // Set up the game world (scene, game objects, etc.)
            void SetupGameWorld(void);

            // Destroy the game world
            void DestroyGameWorld(void);

            // Run the game (keep the game active)
            void MainLoop(void); 

			// placeholders for when we implement them
            void HandleCollision(GameObject*, GameObject*);

        private:
            // Main window: pointer to the GLFW window structure
            GLFWwindow *window_;

            // Sprite geometry
            Geometry *sprite_;

            // Shader for rendering sprites in the scene
            Shader sprite_shader_;

            Shader text_shader_;

            Shader background_shader_;

            Shader particle_shader_;

            // References to textures
            // This needs to be a pointer
            GLuint *tex_;

            // check if space key is pressed
			bool space_key_pressed_; 

            // check if P key is pressed
            bool p_key_pressed_;

            // current projectile state
            ProjectileState current_projectile_state_;

            // List of game objects - player, enemies, collectibles and whatever else we add
            std::vector<GameObject*> game_objects_;

            // Keep track of time
            double current_time_;

            // Handle user input
            void HandleControls(double delta_time);

            // Update all the game objects
            void Update(double delta_time);
 
            // Render the game world
            void Render(void);

            // Callback for when the window is resized
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Set a specific texture
            void SetTexture(GLuint w, const char *fname);

            // Load all textures
            void LoadTextures(std::vector<std::string> &textures);

            // Ray-Circle Collision
            bool RayCircleCollision(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& center, float radius);
            
            // Score counter
            int Score;

            // Timers for enemies
            Timer mole_spawn_timer_;
            Timer bandit_spawn_timer_;
			Timer heart_spawn_timer_;
			Timer ammo_spawn_timer_;

            // Enemy factory
            EnemyFactory enemy_factory_;

            // game over flag
            bool game_over_ = false;

            int pistol_ammo_ = 10;
            int shotgun_ammo_ = 7;

    }; // class Game

} // namespace game

#endif // GAME_H_
