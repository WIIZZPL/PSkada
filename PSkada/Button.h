#pragma once

#include "rectangle.h"

typedef Rectangle Button;

Button* createButton(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp);

void renderButton(Button* thisButton);
int pointCollisionButton(Button* thisButton, int x, int y);

void destroyButton(Button** thisButton);