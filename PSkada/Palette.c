#include "Palette.h"

float paletteSpeed = 0.3;

Palette* createPalette(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	Palette* newPalette = createRectangle(x, y, w, h, bmp);
	newPalette->userParam = (char*)malloc(sizeof(char)); //Ball sticks to pallete?
	if (!newPalette->userParam) exit(138);
	*(char*)newPalette->userParam = 1;
	return newPalette;
}

void updatePalette(Palette* thisPalette, UpgradeDArray* upgrades, double dt, char* keyboardState) {
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
	if (thisPalette->x < 0) thisPalette->x = 0;
	if (thisPalette->x + thisPalette->w > 1) thisPalette->x = 1 - thisPalette->w;

	for(unsigned int i = 0; i < upgrades->size; i++) {
		Upgrade* upgrade = upgrades->arr[i];
		float nx = max(thisPalette->x, min(thisPalette->x + thisPalette->w, upgrade->x));
		float ny = max(thisPalette->y, min(thisPalette->y + thisPalette->h, upgrade->y));
		if (powf(fabsf(nx - upgrade->x), 2) + powf(fabsf(ny - upgrade->y), 2) <= powf(upgrade->r, 2)) {
			switch (*(char*)upgrade->userParam){
			case 0:
				break;
			case 1:
				thisPalette->w += 0.5 / 16;
				min(thisPalette->w, 8.0 / 16);
				break;
			case 2:
				thisPalette->w -= 0.5 / 16;
				max(thisPalette->w, 2.0 / 16);
				break;
			case 3:
				break;
			case 4:
				break;
			}
			removeUpgradeDArray(upgrades, upgrades->arr + i);
		}
	}
}

void renderPalette(Palette* thisPalette) {
	renderRectangle(thisPalette);
}

void destroyPalette(Palette** thisPalette) {
	free((*thisPalette)->userParam);
	destroyRectangle(thisPalette);
}