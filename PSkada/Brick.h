#pragma once

#include "rectangle.h"

typedef Rectangle Brick;

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp);

void renderBrick(Brick* thisBrick);

void destroyBrick(Brick** thisBrick);