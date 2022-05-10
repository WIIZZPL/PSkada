#include "Brick.h"
#include <stdio.h>
int brickCount;

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	Brick* ptr = createRectangle(x, y, w, h, bmp);
	printf("Brick Created! %p (%d)\n", ptr, ++brickCount);
	return ptr;
}

Brick* copyBrick(Brick* brick) {
	printf("Brick Copied! %p (%d)\n", brick, ++brickCount);
	return copyRectangle(brick);
}

void renderBrick(Brick* thisBrick) {
	if (!thisBrick) return;
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	printf("Brick Destroyed! %p (%d)\n", *thisBrick, --brickCount);
	destroyRectangle(thisBrick);
}
