cmake_minimum_required(VERSION 3.18)

# Name of project
set(PROJ_NAME CowboyRushDown)
project(${PROJ_NAME})

# Specify project files: header files and source files
set(HDRS
    file_utils.h
    game.h
    game_object.h
    player_game_object.h
    shader.h
    geometry.h
    sprite.h
    timer.h
    collectible_game_object.h
    enemy_game_object.h
    projectile_game_object.h
    enemy_factory.h
    mole_enemy.h
    bandit_enemy.h
    boss_enemy.h
    healthBar.h
    gunUi.h
    text_game_object.h
    sherrifStar.h
    heart.h
    shield.h
    blocker.h
    particles.h
    particle_system.h
    hand.h
    Tnt.h
    UpperArm.h
    LowerArm.h
   
)
 
set(SRCS
    file_utils.cpp
    game.cpp
    game_object.cpp
    main.cpp
    player_game_object.cpp
    shader.cpp
    sprite.cpp
    sprite_vertex_shader.glsl
    sprite_fragment_shader.glsl
    text_fragment_shader.glsl
    sprite_vertex_shader_2.glsl
    sprite_background_shader.glsl
    particle_fragment_shader.glsl
    particle_vertex_shader.glsl
    timer.cpp
    collectible_game_object.cpp
    enemy_game_object.cpp
    projectile_game_object.cpp
    enemy_factory.cpp
    mole_enemy.cpp
    bandit_enemy.cpp
    boss_enemy.cpp
    healthBar.cpp
    gunUi.cpp
    text_game_object.cpp
    sherrifStar.cpp
    heart.cpp
    shield.cpp
    blocker.cpp
    particles.cpp
    particle_system.cpp
    Hand.cpp
    Tnt.cpp
    UpperArm.cpp
    LowerArm.cpp

)

# Add path name to configuration file
configure_file(path_config.h.in path_config.h)

# Add executable based on the source files
add_executable(${PROJ_NAME} ${HDRS} ${SRCS})

# Directories to include for header files, so that the compiler can find
# path_config.h
target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Require OpenGL library
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH $ENV{COMP2501_LIBRARY_PATH} CACHE PATH "Folder with GLEW, GLFW, GLM, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${PROJ_NAME} ${GLEW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX _d)

    # Set the default project in VS
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME})
endif(WIN32)
