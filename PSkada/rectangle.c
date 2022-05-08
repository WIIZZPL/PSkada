#include "rectangle.h"

Rectangle* createRectangle(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	Rectangle* newRectangle = (Rectangle*)malloc(sizeof(Rectangle));
	if (!newRectangle || !bmp) exit(138);
	newRectangle->x = x;
	newRectangle->y = y;
	newRectangle->w = w;
	newRectangle->h = h;
	newRectangle->bmp = bmp;
	return newRectangle;
}

void renderRectangle(Rectangle* rectangle) {
	al_draw_scaled_bitmap(rectangle->bmp, 0, 0, al_get_bitmap_width(rectangle->bmp), al_get_bitmap_height(rectangle->bmp),
		rectangle->x * displayWidth + displayX, rectangle->y * displayHeight + displayY, rectangle->w * displayWidth, rectangle->h * displayHeight, 0);
}

int pointCollisionRectangle(Rectangle* rectangle, int x, int y) {
	return x >= rectangle->x*displayWidth+displayX && x <= rectangle->x*displayWidth+displayX + rectangle->w*displayWidth &&
		   y >= rectangle->y*displayHeight+displayY && y <= rectangle->y*displayHeight+displayY + rectangle->h*displayHeight;
}

void destroyRectangle(Rectangle* rectangle) {
	if (!rectangle) return;
	al_destroy_bitmap(rectangle->bmp);
	free(rectangle);
}