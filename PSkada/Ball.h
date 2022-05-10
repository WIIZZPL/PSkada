#pragma once

#include "circle.h"
#include "Palette.h"
#include "Brick.h"
#include "BrickQTree.h"
#include <math.h>

typedef Circle Ball;

Ball* createBall(float x, float y, float r, ALLEGRO_BITMAP* bmp);

void updateBall(Ball** thisBall, Palette* palette, BrickDArray* bricks, BrickQTree* bricksQTree, double dt);
void renderBall(Ball* thisBall, double lag);
void brickQTreeBallColission(Ball* thisBall, BrickDArray* bricks, BrickQTree* bricksQTree);

void destroyBall(Ball** thisBall);