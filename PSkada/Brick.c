#include "Brick.h"

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	return createRectangle(x, y, w, h, bmp);
}

void renderBrick(Brick* thisBrick) {
	if (!thisBrick) return;
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	destroyRectangle(thisBrick);
}