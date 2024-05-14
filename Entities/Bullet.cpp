#include "Bullet.h"
#include <iostream>
#include <GL/freeglut.h>
#include <SDL.h>
#include <SDL_mixer.h>

Bullet::Bullet() : position({ 0.0f, 0.0f }), active(false), sound(nullptr) {}

void Bullet::fire(float x, float y) {
    position.x = x;
    position.y = y;
    active = true;

    // Load sound if not already loaded
    if (sound == nullptr) {
        sound = Mix_LoadWAV("sound/fire.wav");
        if (sound == nullptr) { 
            std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
        }
    }

    // Play the loaded sound
    if (sound != nullptr) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

void Bullet::update() {
    if (active) {
        position.y += 0.02;
    }
}

void Bullet::render() {
    if (active) {
        glPushMatrix();
            glTranslatef(position.x, position.y, 0.0);
            Bullet shape;
            glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.01, 0.01);
        glVertex2f(0.01, 0.01);
        glVertex2f(0.01, -0.01);
        glVertex2f(-0.01, -0.01);
        glEnd();
        glPopMatrix();
    }
}

bool Bullet::isActive() const {
    return active;
}

void Bullet::deactivate() {
    active = false;
}

Position Bullet::getPosition() const {
    return position;
}