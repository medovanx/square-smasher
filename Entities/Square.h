#ifndef SQUARE_H
#define SQUARE_H

#include "Position.h"

class Square {
private:
    Position position;
    bool destroyed;

public:
    Square(float x, float y);
    void render();
    bool isDestroyed();
    bool checkCollision(float bulletX, float bulletY);
    Position getPosition() const;
};

#endif // SQUARE_H