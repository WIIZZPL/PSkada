#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GLOBALVARS.h"
#include "rectangle.h"

typedef struct Circle {
	float x, y, r;
	float speed[2];
	float acceleration[2];
	ALLEGRO_BITMAP* bmp;
} Circle;

Circle* createCircle(float x, float y, float r, float speed[2], float acceleration[2], ALLEGRO_BITMAP* bmp);
void renderCircle(Circle* thisCircle, double lag);
void destroyCircle(Circle* thisCircle);
