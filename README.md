# Square Smasher

Square Smasher is a simple game implemented using OpenGL and GLUT. The goal of the game is to destroy all the green squares by shooting bullets from a spaceship before time runs out.

## Features

- Shoot bullets from the spaceship to destroy green squares
- Keep track of your score as you destroy squares
- Win the game by destroying all squares
- Restart the game by pressing 'Q' after winning

## Dependencies

- freeglut
- SDL2
- SDL_mixer

## Installation

### Using Visual Studio (NuGet Package Manager)
1. Clone this repository to your local machine.

2. Open the project in Visual Studio.

#### Installing freeglut

- Install the `nupengl.core` package:
   - Open the Package Manager Console (Tools > NuGet Package Manager > Package Manager Console).
   - Run the following command:
     ```
     Install-Package nupengl.core
     ```

#### Installing SDL
- Follow the tutorial from [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).


Finally Build and run the project.

## How to Play

- Move the spaceship by moving your mouse.
- Click the left mouse button to fire bullets at the green squares.
- Aim to destroy all the squares to win the game.
- After winning, press 'Q' to restart the game.

## Screenshots

<p align="center">
  <img src="https://github.com/medovanx/square-smasher/assets/29468096/e5af6dc9-86ea-4360-b3e1-0a7ec65ddffc" width="49%">
  <img src="https://github.com/medovanx/square-smasher/assets/29468096/d07b3da0-760f-461f-9b09-4aaf9599e2a8" width="49%">
</p>