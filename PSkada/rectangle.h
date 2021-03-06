#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "GLOBALVARS.h"

typedef struct Rectangle {
	float x, y, w, h;
	ALLEGRO_BITMAP* bmp;
	void* userParam;
} Rectangle;

Rectangle* createRectangle(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp);
Rectangle* copyRectangle(Rectangle* rectangle);

void renderRectangle(Rectangle* thisRectangle);

void destroyRectangle(Rectangle** thisRectangle);