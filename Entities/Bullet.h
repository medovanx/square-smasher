#ifndef BULLET_H
#define BULLET_H

#include "Position.h"
#include <SDL_mixer.h>

class Bullet {
private:
    Position position;
    bool active;
    Mix_Chunk* sound; // Pointer to an SDL audio chunk
public:
    Bullet();
    void playFireSound();
    void fire(float x, float y);
    void update();
    void render();
    bool isActive() const;
    void deactivate();
    Position getPosition() const;
};

#endif // BULLET_H