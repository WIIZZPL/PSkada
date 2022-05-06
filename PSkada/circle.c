#include "circle.h"

Circle* createCircle(float x, float y, float r, float speed[2], float acceleration[2], ALLEGRO_COLOR color) {
	Circle* newCircle = (Circle*)malloc(sizeof(Circle));
	if (!newCircle) exit(138);
	newCircle->x = x;
	newCircle->y = y;
	newCircle->r = r;
	newCircle->speed[0] = speed[0];
	newCircle->speed[1] = speed[1];
	newCircle->acceleration[0] = acceleration[0];
	newCircle->acceleration[1] = acceleration[1];
	newCircle->color = color;
	return newCircle;
}

void updateCircle(Circle* thisCirlce, double dt) {
	thisCirlce->speed[0] += thisCirlce->acceleration[0] * dt;
	thisCirlce->speed[1] += thisCirlce->acceleration[1] * dt;
	thisCirlce->x += thisCirlce->speed[0] * dt;
	thisCirlce->y += thisCirlce->speed[1] * dt;
	//COLLISION
	if (thisCirlce->x + thisCirlce->r > 1 || thisCirlce->x - thisCirlce->r < 0) {
		thisCirlce->speed[0] *= -1;
		max(thisCirlce->r, thisCirlce->x);
		min(1 - thisCirlce->r, thisCirlce->x);
	}
	if (thisCirlce->y + thisCirlce->r > 1 || thisCirlce->y - thisCirlce->r < 0) {
		thisCirlce->speed[1] *= -1;
		max(thisCirlce->r, thisCirlce->y);
		min(1 - thisCirlce->r, thisCirlce->y);
	}
}

void renderCircle(Circle* thisCircle, double lag) {
	float x = thisCircle->x;
	float y = thisCircle->y;
	
	//LAG COMPENSATION
	//x += thisCircle->speed[0] * lag;
	//y += thisCircle->speed[1] * lag;

	al_draw_filled_circle(x * displayWidth + displayX, y * displayHeight + displayY, thisCircle->r * displayWidth, thisCircle->color);
}

void destroyCircle(Circle* thisCircle) {
	if (!thisCircle) return;
	free(thisCircle);
}