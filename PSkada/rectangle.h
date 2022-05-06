#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "GLOBALVARS.h"

typedef struct Rectangle {
	float x, y, w, h;
	ALLEGRO_BITMAP* background;
} Rectangle;

Rectangle* createRectangle(float x, float y, float w, float h, ALLEGRO_BITMAP* background);

void renderRectangle(Rectangle* rectangle);

int pointCollisionRectangle(Rectangle* rectangle, int x, int y);

void destroyRectangle(Rectangle* rectangle);