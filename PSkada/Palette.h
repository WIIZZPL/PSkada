#pragma once

#include "rectangle.h"
#include "UpgradeDArray.h"
#include "Upgrade.h"
#include <math.h>

typedef Rectangle Palette;

Palette* createPalette(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp);

void updatePalette(Palette* thisPalette, UpgradeDArray* upgrades, double dt, char* keyboardState);
void renderPalette(Palette* thisPalette);

void destroyPalette(Palette** thisPalette);