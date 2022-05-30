#include "Brick.h"

Brick* createBrick(float x, float y) {
	ALLEGRO_BITMAP* bmp = al_load_bitmap("przyciskStart.png");
	return createRectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT, bmp);
}

void renderBrick(Brick* thisBrick) {
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	destroyRectangle(thisBrick);
}
