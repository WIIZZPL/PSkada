#pragma once

#include "circle.h"
#include "Palette.h"
#include <math.h>

typedef Circle Ball;

Ball* createBall(float x, float y, float r, ALLEGRO_BITMAP* bmp);

void updateBall(Ball* thisBall, Palette* palette, double dt);
void renderBall(Ball* thisBall, double lag);

void destroyBall(Ball* thisBall);