#include "Brick.h"

Brick* createBrick(float x, float y) {
	char brickType = rand() % 8;
	char bmpFileName_b[16];
	snprintf(bmpFileName_b, 16, "brick%d.png", brickType);
	ALLEGRO_BITMAP* bmp = al_load_bitmap(bmpFileName_b);
	if (!bmp) exit(138);
	return createRectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT, bmp);

}

void renderBrick(Brick* thisBrick) {
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	destroyRectangle(thisBrick);
}
