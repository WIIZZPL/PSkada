#pragma once

#include "rectangle.h"

typedef Rectangle Brick;

#define BRICK_WIDTH (1.0/16)
#define BRICK_HEIGHT (0.5/9)

Brick* createBrick(float x, float y);

void renderBrick(Brick* thisBrick);

void destroyBrick(Brick** thisBrick);