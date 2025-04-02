#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shader.h"
#include "game_object.h"
#include "player_game_object.h"
#include "collectible_game_object.h"
#include "enemy_game_object.h"
#include "projectile_game_object.h"

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
				tex_boss = 1,
                tex_item = 2,
				tex_pistol = 3,
				tex_shotgun = 4,
				tex_bullet = 5,
				tex_wildwest = 6
            };

            // Set up the game world (scene, game objects, etc.)
            void SetupGameWorld(void);

            // Destroy the game world
            void DestroyGameWorld(void);

            // Run the game (keep the game active)
            void MainLoop(void); 

			// placeholders for when we implement them
            void HandleCollision();

        private:
            // Main window: pointer to the GLFW window structure
            GLFWwindow *window_;

            // Sprite geometry
            Geometry *sprite_;

            // Shader for rendering sprites in the scene
            Shader sprite_shader_;

            // References to textures
            // This needs to be a pointer
            GLuint *tex_;

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

    }; // class Game

} // namespace game

#endif // GAME_H_
