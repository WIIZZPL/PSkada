#include "Brick.h"

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	Brick* ptr = createRectangle(x, y, w, h, bmp);
	return ptr;
}

Brick* copyBrick(Brick* brick) {
	return copyRectangle(brick);
}

void renderBrick(Brick* thisBrick) {
	if (!thisBrick) return;
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	destroyRectangle(thisBrick);
}
