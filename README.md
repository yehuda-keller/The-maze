# The Maze

![The Maze]([https://www.youtube.com/watch?v=M3Er4vI04j0&t=2s])

## Introduction

"The Maze" is an original game developed using the SFML graphical library. The game consists of two levels where the player's character must collect two goblets in each level to pass through a door and advance to the next stage. Players must avoid enemies; colliding with an enemy will return the player to the start of the stage. All actions must be completed within a given time limit, or the player will be reset to the beginning of the stage.

## Gameplay

- The game starts with an opening screen featuring a menu with three options: Start Game, Information about game objects, and Exit.
- In the information option, players can return to the main menu.
- The main character can move up, down, left, and right using the keyboard arrows.
- Levels are stored in the resources folder with names: Board1.txt, Board2.txt. To add a new level, add it to the folder with the next consecutive name and update the CMake file.
- The game will read the number of rows, columns, and time limit for each level from the level files. Characters and tiles are designated as follows:
  - Main Character: `P`
  - Enemy: `E`
  - Wall: `#`
  - Door: `D`
  - Empty Tile: ` ` (space)

## Design

The game includes:
- A main character that can move in four directions.
- Levels designed and stored in text files.
- An animation system.
- Collision handling.
- Event management.
- A variety of objects including goblets, doors, enemies, and walls.

## Files

- **Header Files:**
  - `Animation.h`: Manages animations.
  - `Board.h`: Reads levels and moves characters on the screen.
  - `CollisionHandling.h`: Handles collisions.
  - `GameController.h`: Manages real-time events on the screen.
  - `Door.h`: Manages the door.
  - `GameObjects.h`: General class for all game objects.
  - `Goblet.h`: Manages the goblets.
  - `Graph.h`: Manages the DFS algorithm.
  - `Enemy.h`: Manages the enemies.
  - `EmptyTile.h`: Manages empty tiles.
  - `Menu.h`: Manages the game's opening screen and menu.
  - `MovingObjects.h`: General class for all moving objects in the game.
  - `Player.h`: Manages the main character.
  - `GameResources.h`: Singleton pattern for loading and accessing all resources such as textures and music.
  - `StaticObjects.h`: General class for all static objects in the game.
  - `InfoBar.h`: Manages the information bar in the game.
  - `Wall.h`: Manages the walls.

- **CPP Files:**
  - `Animation.cpp`: Implements animation functions.
  - `Board.cpp`: Implements the level and character movement.
  - `CollisionHandling.cpp`: Implements collision functions.
  - `GameController.cpp`: Implements real-time event management.
  - `Door.cpp`: Implements door functions.
  - `GameObjects.cpp`: Implements object management.
  - `Enemy.cpp`: Implements enemy functions.
  - `Main.cpp`: Main function that starts the game controller.
  - `Menu.cpp`: Implements the menu functions.
  - `MovingObjects.cpp`: Implements moving object management.
  - `Player.cpp`: Implements the main character functions.
  - `Resources.cpp`: Implements the Singleton pattern for resource management.
  - `StaticObjects.cpp`: Implements static object management.
  - `InfoBar.cpp`: Implements the information bar functions.
  - `Wall.cpp`: Implements wall functions.

## Known Bugs

- List any known bugs here.

## Images

![Main Menu](path_to_your_image2)
![Gameplay](path_to_your_image3)
![Instructions](path_to_your_image4)
![Menu Again](path_to_your_image5)

