#include "Button.h"

Button* createButton(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	return createRectangle(x, y, w, h, bmp);
}

void renderButton(Button* thisButton) {
	renderRectangle(thisButton);
}

int pointCollisionButton(Button* thisButton, int x, int y) {
	return x >= thisButton->x * displayWidth + displayX && x <= thisButton->x * displayWidth + displayX + thisButton->w * displayWidth &&
		y >= thisButton->y * displayHeight + displayY && y <= thisButton->y * displayHeight + displayY + thisButton->h * displayHeight;
}

void destroyButton(Button** thisButton) {
	destroyRectangle(thisButton);
}