#pragma once

#include "circle.h"
#include "Palette.h"
#include "Brick.h"
#include "BrickQTree.h"
#include "Upgrade.h"
#include "UpgradeDArray.h"
#include <math.h>

typedef Circle Ball;

Ball* createBall(float x, float y, float r, ALLEGRO_BITMAP* bmp);

void updateBall(Ball** thisBall, Palette* palette, BrickDArray* bricks, BrickQTree* bricksQTree, UpgradeDArray* upgrades, double dt);
void renderBall(Ball* thisBall, double lag);
void brickQTreeBallColission(Ball* thisBall, BrickDArray* bricks, BrickQTree* bricksQTree, UpgradeDArray* upgrades);

void destroyBall(Ball** thisBall);