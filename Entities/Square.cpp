#include "Square.h"
#include "Position.h"
#include <GL/freeglut.h>
extern const float squareSize;

Square::Square(float x, float y) : position({ x, y }), destroyed(false) {}

void Square::render() {
    if (!destroyed) {
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + squareSize, position.y);
        glColor3f(0.5, 0.7, 0.3);
        glVertex2f(position.x + squareSize, position.y - squareSize);
        glColor3f(0.4, 1.0, 0.8);
        glVertex2f(position.x, position.y - squareSize);
        glEnd();
    }
}

bool Square::isDestroyed() {
    return destroyed;
}

bool Square::checkCollision(float bulletX, float bulletY) {
    if (!destroyed && bulletX >= position.x && bulletX <= position.x + squareSize &&
        bulletY <= position.y && bulletY >= position.y - squareSize) {
        destroyed = true;
        return true;
    }
    return false;
}

Position Square::getPosition() const {
    return position;
}