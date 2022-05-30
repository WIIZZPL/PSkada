#include "Palette.h"

float paletteSpeed = 0.3;

Palette* createPalette(float x, float y, float w, float h) {
	ALLEGRO_BITMAP* bmp = al_load_bitmap("palette.png");
	Palette* newPalette = createRectangle(x, y, w, h, bmp);
	newPalette->userParam = (char*)malloc(sizeof(char)); //Ball sticks to pallete?
	if (!newPalette->userParam) exit(138);
	*(char*)newPalette->userParam = 1;
	return newPalette;
}

void movePalette(Palette* thisPalette, double dt, char* keyboardState) {
	if (keyboardState[ALLEGRO_KEY_LEFT]) {
		thisPalette->x -= paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_LEFT] = keyboardState[ALLEGRO_KEY_LEFT] ^ 2;
	}
	if (keyboardState[ALLEGRO_KEY_RIGHT]) {
		thisPalette->x += paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_RIGHT] = keyboardState[ALLEGRO_KEY_RIGHT] ^ 2;
	}
	if (keyboardState[ALLEGRO_KEY_SPACE]) {
		thisPalette->userParam = 0;
		keyboardState[ALLEGRO_KEY_SPACE] = keyboardState[ALLEGRO_KEY_SPACE] ^ 2;
	}
}

void renderPalette(Palette* thisPalette) {
	renderRectangle(thisPalette);
}

void destroyPalette(Palette** thisPalette) {
	free((*thisPalette)->userParam);
	destroyRectangle(thisPalette);
}