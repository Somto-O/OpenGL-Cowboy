# OpenGL-Cowboy

![Language](https://img.shields.io/badge/language-C++-blue.svg)
![Library](https://img.shields.io/badge/OpenGL-GLFW%2FGLM-green.svg)
![Status](https://img.shields.io/badge/status-In%20Development-orange.svg)

A top-down shooter game created using the **GLFW** and **GLM** libraries.

---

## 🎮 Controls

- **WASD** – Move the player  
- **P** – Switch between weapons (Pistol / Shotgun)  
- **SPACE** – Fire weapon  

---

## 🏆 Goal of the Game

**Defeat the Boss and go for the high score!**  
Get at least **5 points** to spawn the Boss. Survive, shoot, and outmaneuver enemies to win.

---

## 🧠 Game Overview

You play as a cowboy taking on a growing horde of bandits in a scrolling game world. Defeat enemies, collect items, dodge bullets, and eventually challenge the powerful Boss!

---

## 📦 Features

### 1. Game Mechanics

- Dodge an increasing number of bullets and enemies.
- Reach a minimum score to spawn and fight the Boss.

### 2. Enemies

- **Moles** – Passive unless attacked. Once provoked, they chase and tackle the player.
- **Bandits** – Periodically shoot at the player and engage at close range, but back off when approached.
- **Boss** – A stationary, large enemy that throws TNT at the player. No movement, but high damage potential.

### 3. Weapons

- **Pistol** – Fires one bullet straight ahead. Fast reload time.
- **Shotgun** – Fires three bullets in a triangular spread. Slower reload time.
- Switch weapons anytime with **P**. The UI shows which one is currently equipped.

### 4. Collectible Items

- **Heart** – Restores 1 heart (Max: 5).
- **Ammo** – Refills the player's ammo.
- **Shield** – Reflects up to 3 bullets (not TNT). Forms a barrier in front of the player.
- **Star** – Greatly reduces reload time for 5 seconds (does **not** give infinite ammo).

### 5. Movement and Transformations

- All movement uses transformation matrices.
- The player uses **physically-based motion**.
- Moles use **parametric motion** while patrolling.

### 6. Collision Detection

- **Ray-Circle** and **distance-based** collision systems are used for bullets and items.

### 7. Game World

- The world is larger than the screen; the camera scrolls with the player.
- Background textures are **tiled** to seamlessly repeat.

### 8. Particle Systems

- **None** used in this version.

### 9. Hierarchical Transformations

- The Boss's arms use a **hierarchical transformation chain** with at least 3 links.

### 10. UI

- Displays **Health**, **Score**, **Time**, and **Current Weapon**.

### 11. Advanced Features

- **Collision Resolution** – Bullets can bounce off shields.
- **Steering Behaviors** – Moles switch between passive and aggressive states based on player interaction.

---

## 🚀 Installation & Run Instructions

1. Download and install **Visual Studio 2022** on your machine.
2. Clone the repository:

   ```bash
   git clone https://github.com/Somto-O/OpenGL-Cowboy.git
3. Open Visual Studio 2022 and select "Open a project or solution", then open the project folder.
4. Wait approximately 1 minute for Visual Studio to compile and select a startup item.
5. Press Run.
