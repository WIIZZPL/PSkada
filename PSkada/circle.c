#include "circle.h"

Circle* createCircle(float x, float y, float r, float speed[2], float acceleration[2], ALLEGRO_BITMAP* bmp) {
	Circle* newCircle = (Circle*)malloc(sizeof(Circle));
	if (!newCircle) exit(138);
	newCircle->x = x;
	newCircle->y = y;
	newCircle->r = r;
	newCircle->speed[0] = speed[0];
	newCircle->speed[1] = speed[1];
	newCircle->acceleration[0] = acceleration[0];
	newCircle->acceleration[1] = acceleration[1];
	newCircle->bmp = bmp;
	return newCircle;
}

void renderCircle(Circle* thisCircle, double lag) {
	float x = thisCircle->x;
	float y = thisCircle->y;
	float r = thisCircle->r;
	
	//LAG COMPENSATION
	x += thisCircle->speed[0] * lag;
	y += thisCircle->speed[1] * lag;

	//COORDINATE CONVERSION
	x = x * displayWidth + displayX;
	y = y * displayHeight + displayY;
	r = r * displayWidth;

	al_draw_scaled_bitmap(thisCircle->bmp, 0, 0, al_get_bitmap_width(thisCircle->bmp), al_get_bitmap_height(thisCircle->bmp),
		x - r, y - r, r * 2, r * 2, 0);
}

void destroyCircle(Circle** thisCircle) {
	if (!*thisCircle) return;
	al_destroy_bitmap((*thisCircle)->bmp);
	free(*thisCircle);
	*thisCircle = NULL;
}