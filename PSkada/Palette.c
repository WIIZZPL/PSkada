#include "Palette.h"

float paletteSpeed = 0.3;

Palette* createPalette(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	return createRectangle(x, y, w, h, bmp);
}

void updatePalette(Palette* thisPalette, double dt, char* keyboardState) {
	if (keyboardState[ALLEGRO_KEY_LEFT]) {
		thisPalette->x -= paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_LEFT] = keyboardState[ALLEGRO_KEY_LEFT] ^ 2;
	}
	if (keyboardState[ALLEGRO_KEY_RIGHT]) {
		thisPalette->x += paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_RIGHT] = keyboardState[ALLEGRO_KEY_RIGHT] ^ 2;
	}
	if (thisPalette->x < 0) thisPalette->x = 0;
	if (thisPalette->x + thisPalette->w > 1) thisPalette->x = 1 - thisPalette->w;
}

void renderPalette(Palette* thisPalette) {
	renderRectangle(thisPalette);
}

void destroyPalette(Palette* thisPalette) {
	destroyRectangle(thisPalette);
}