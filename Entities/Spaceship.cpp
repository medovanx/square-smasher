#include "Spaceship.h"
#include <GL/freeglut.h>
extern int windowWidth;
extern int windowHeight;

Spaceship::Spaceship() : position({ 0, -0.9 }) {}

void Spaceship::updatePosition(int x, int y) {
    position.x = (x - windowWidth / 2) * 2.0 / windowWidth;
    position.y = (windowHeight / 2 - y) * 2.0 / windowHeight;
}

void Spaceship::render() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0);

    // Body
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.1, 0.1); // Red
    glVertex2f(0.0, 0.1);
    glColor3f(0.3, 0.7, 0.9); // Light blue
    glVertex2f(-0.06, -0.1);
    glColor3f(0.3, 0.7, 0.9); // Light blue
    glVertex2f(0.06, -0.1);
    glEnd();

    // Wings
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.5); // Dark gray
    glVertex2f(-0.05, 0.05);
    glColor3f(0.8, 0.8, 0.8); // Light gray
    glVertex2f(-0.15, -0.05);
    glColor3f(0.3, 0.7, 0.9); // Light blue
    glVertex2f(-0.05, -0.05);

    glColor3f(0.5, 0.5, 0.5); // Dark gray
    glVertex2f(0.05, 0.05);
    glColor3f(0.8, 0.8, 0.8); // Light gray
    glVertex2f(0.15, -0.05);
    glColor3f(0.3, 0.7, 0.9); // Light blue
    glVertex2f(0.05, -0.05);
    glEnd();

    glPopMatrix();
}