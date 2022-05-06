#include "rectangle.h"

Rectangle* createRectangle(float x, float y, float w, float h, ALLEGRO_BITMAP* background) {
	if (!background) exit(138);
	Rectangle* newRectangle = (Rectangle*)malloc(sizeof(Rectangle));
	if (!newRectangle) return NULL;
	newRectangle->x = x;
	newRectangle->y = y;
	newRectangle->w = w;
	newRectangle->h = h;
	newRectangle->background = background;
	return newRectangle;
}

void renderRectangle(Rectangle* rectangle) {
	if (!rectangle) exit(138);
	al_draw_scaled_bitmap(rectangle->background, 0, 0, al_get_bitmap_width(rectangle->background), al_get_bitmap_height(rectangle->background),
		rectangle->x * displayWidth + displayX, rectangle->y * displayHeight + displayY, rectangle->w * displayWidth, rectangle->h * displayHeight, 0);
}

int pointCollisionRectangle(Rectangle* rectangle, int x, int y) {
	return x >= rectangle->x*displayWidth+displayX && x <= rectangle->x*displayWidth+displayX + rectangle->w*displayWidth &&
		   y >= rectangle->y*displayHeight+displayY && y <= rectangle->y*displayHeight+displayY + rectangle->h*displayHeight;
}

void destroyRectangle(Rectangle* rectangle) {
	if (!rectangle) return;
	al_destroy_bitmap(rectangle->background);
	free(rectangle);
}