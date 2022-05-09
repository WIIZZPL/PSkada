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

Rectangle* copyRectangle(Rectangle* rectangle) {
	Rectangle* newRectangle = (Rectangle*)malloc(sizeof(Rectangle));
	if (!newRectangle) exit(138);
	newRectangle->x = rectangle->x;
	newRectangle->y = rectangle->y;
	newRectangle->w = rectangle->w;
	newRectangle->h = rectangle->h;
	newRectangle->bmp = al_clone_bitmap(rectangle->bmp);
	return newRectangle;
}

void renderRectangle(Rectangle* thisRectangle) {
	al_draw_scaled_bitmap(thisRectangle->bmp, 0, 0, al_get_bitmap_width(thisRectangle->bmp), al_get_bitmap_height(thisRectangle->bmp),
		thisRectangle->x * displayWidth + displayX, thisRectangle->y * displayHeight + displayY, thisRectangle->w * displayWidth, thisRectangle->h * displayHeight, 0);
}

void destroyRectangle(Rectangle** thisRectangle) {
	if (!*thisRectangle) return;
	al_destroy_bitmap((*thisRectangle)->bmp);
	free(*thisRectangle);
	*thisRectangle = NULL;
}