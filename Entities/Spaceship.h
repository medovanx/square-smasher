#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Position.h"

class Spaceship {
private:
    Position position;

public:
    Spaceship();
    void updatePosition(int x, int y);
    void render();
};

#endif // SPACESHIP_H