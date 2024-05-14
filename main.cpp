#include <GL/freeglut.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include "Entities/Bullet.h"
#include "Entities/Square.h"
#include "Entities/Spaceship.h"

// Define window dimensions
extern int windowWidth = 800;
extern int windowHeight = 600;

// Grid parameters
int rows;
int cols;
float gridWidth;
float gridHeight;

// Define square parameters
extern const float squareSize = 0.1; // Size of each square
const float borderWidth = 0.005; // Border width between squares

// Define grid start position
float startX;
float startY;

// Define score variables
int score = 0;
bool gameWon = false;
bool gameStarted = false;
bool gridInitialized = false;
bool youWonSoundPlayed = false;
bool gameOverSoundPlayerd = false;
// Define time variables
int startTime = 0;
int timeLimit = 10;
bool gameOver = false;

// Bullet vector to store active bullets
std::vector<Bullet> bullets;

// Square vector to store grid squares
std::vector<Square> squares;

// Spaceship instance
Spaceship spaceship;

// Function prototypes
void createGrid();
void onMouseClick(int button, int state, int x, int y);
void init();
void display();
void update(int value);
void onMouseMove(int x, int y);
void onKeyPress(unsigned char key, int x, int y);

int main(int argc, char** argv) {
    // Initialize SDL audio subsystem
    SDL_Init(SDL_INIT_AUDIO);
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    // Initialize SDL Mixer audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Initialize freeglut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Square Smasher");

    // Set up OpenGL
    init();

    // Set callback functions
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutPassiveMotionFunc(onMouseMove);
    glutKeyboardFunc(onKeyPress);

    // Start the main loop
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

void createGrid() {
    if (!gridInitialized) {
        // Randomly determine rows and cols
        rows = rand() % 4 + 1; // Random number from 1 to 4
        cols = rand() % 4 + 1; // Random number from 1 to 4

        // Calculate grid width and height
        gridWidth = cols * (squareSize + borderWidth);
        gridHeight = rows * (squareSize + borderWidth);

        // Calculate grid start position
        startX = -gridWidth / 2.0; // Start from the left edge
        startY = gridHeight / 2.0; // Start from the top edge

        // Create squares
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                float x = startX + col * (squareSize + borderWidth);
                float y = startY - row * (squareSize + borderWidth);
                squares.push_back(Square(x, y));
            }
        }


        // Set gridInitialized to true
        gridInitialized = true;
    }

    // Render squares only if the grid is initialized
    if (gridInitialized) {
        for (auto& square : squares) {
            square.render();
        }
    }
}

void onMouseClick(int button, int state, int x, int y) {
    if (!gameStarted) {
        // If the game hasn't started, ignore the left-click event
        return;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float posX = (x - windowWidth / 2) * 2.0 / windowWidth;
        float posY = (windowHeight / 2 - y) * 2.0 / windowHeight;

        // Fire a bullet at the click position
        Bullet bullet;
        bullet.fire(posX, posY);
        bullets.push_back(bullet);
    }
}

void init() {
    glClearColor(0.1, 0.2, 0.2, 1.0);

    Mix_Chunk* startSound = Mix_LoadWAV("sound/are_u_ready.wav");
    if (startSound != nullptr) {
        Mix_PlayChannel(-1, startSound, 0);
    }

    glutSetCursor(GLUT_CURSOR_NONE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameStarted) {
        createGrid();

        // Render the spaceship
        spaceship.render();

        // Render and update bullets
        for (auto& bullet : bullets) {
            bullet.update();
            bullet.render();

            // Check collision with squares
            for (auto& square : squares) {
                if (square.checkCollision(bullet.getPosition().x, bullet.getPosition().y)) {
                    bullet.deactivate();
                    if (square.isDestroyed()) {
                        score++;
                    }
                    break;
                }
            }

            // Deactivate bullets that go off the screen
            if (bullet.getPosition().y > 1.0)
                bullet.deactivate();
        }

        // Display score
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.95, 0.9);
        std::string scoreText = "Score: " + std::to_string(score);
        for (char c : scoreText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }

        // Calculate remaining time
        int currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000; // Convert milliseconds to seconds
        int remainingTime = timeLimit - (currentTime - startTime);

        // Update and display game time
        if (remainingTime > 0 && !gameWon) {
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2f(-0.95, 0.8);
            std::string timeText = "Time: " + std::to_string(remainingTime);
            for (char c : timeText) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
            }
        }
        else {
            // Display game over or win message
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2f(-0.5, 0.0);
            std::string messageText;
            if (gameWon) {
                messageText = "You Won! Press Q to restart.";
            }
            else {
                messageText = "Game Over! Press Q to restart.";
                gameOver = true;
                squares.clear();
                // Play game over sound if it hasn't been played yet
                if (!gameOverSoundPlayerd) {
                    Mix_Chunk* gameOverSound = Mix_LoadWAV("sound/game_over.wav");
                    if (gameOverSound != nullptr) {
                        Mix_PlayChannel(-1, gameOverSound, 0);
                        gameOverSoundPlayerd = true;
                    }
                }
            }
            for (char c : messageText) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
            }
        }

        // Check win condition
        if (score == rows * cols && !gameWon && !gameOver) {
            gameWon = true;
            // Stop the countdown
            remainingTime = 0;
            if (!youWonSoundPlayed) {
                Mix_Chunk* startSound = Mix_LoadWAV("sound/congrats.wav");
                if (startSound != nullptr) {
                    Mix_PlayChannel(-1, startSound, 0);
                    youWonSoundPlayed = true;
                }
            }
        }
    }
    else {
        // Display start message
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.5, 0.0);
        std::string startText = "Press S to start the game";
        for (char c : startText) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    }

    glutSwapBuffers();
}

void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void onMouseMove(int x, int y) {
    spaceship.updatePosition(x, y);
    glutPostRedisplay();
}

void onKeyPress(unsigned char key, int x, int y) {
    if (!gameStarted && (key == 's' || key == 'S')) {
        gameStarted = true;
        // Set start time
        startTime = glutGet(GLUT_ELAPSED_TIME) / 1000; // Convert milliseconds to seconds
        // Play sound when game starts
        Mix_Chunk* startSound = Mix_LoadWAV("sound/im_ready.wav");
        if (startSound != nullptr) {
            Mix_PlayChannel(-1, startSound, 0);
        }
        gridInitialized = false;
    }
    else if ((gameWon || gameOver) && (key == 'q' || key == 'Q')) {
        // Reset game state
        score = 0;
        gameWon = false;
        gameOver = false; // Reset game over flag
        squares.clear(); // Clear existing squares
        gridInitialized = false; // Reset grid initialization flag
        bullets.clear();
        // Reset start time
        startTime = glutGet(GLUT_ELAPSED_TIME) / 1000; // Convert milliseconds to seconds
        for (auto& square : squares) {
            square = Square(square.getPosition().x, square.getPosition().y);
        }
        // Reset sound flags
        youWonSoundPlayed = false;
        gameOverSoundPlayerd = false;
        Mix_Chunk* startSound = Mix_LoadWAV("sound/lets_go.wav");
        if (startSound != nullptr) {
            Mix_PlayChannel(-1, startSound, 0);
        }
    }
}