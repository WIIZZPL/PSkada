#include "Upgrade.h"

Upgrade* createUpgrade(float x, float y) {
	float speed[2] = { 0.15, -0.3 };
	if (x > 0.5) speed[0] *= -1;
	float acceleration[2] = { 0.0, 1.0 };
	
	char upgradeType = rand()%6; //types of upgrades

	/*
	0 - Penetrating ball
	1 - Wider Palette
	2 - Thinner Palette
	3 - Faster balls
	4 - Slower balls
	5 - Duplicate balls
	*/

	char bmpFileName[16];
	snprintf(bmpFileName, 16, "upgrade%d.png", upgradeType);
	ALLEGRO_BITMAP* bmp = al_load_bitmap(bmpFileName);
	if (!bmp) exit(138);

	Upgrade* newUpgrade = createCircle(x, y, UPGRADE_RADIUS, speed, acceleration, bmp);

	newUpgrade->userParam = (char*)malloc(sizeof(char));
	if (!newUpgrade->userParam) exit(138);
	*(char*)newUpgrade->userParam = upgradeType; //Non-Penetrating. if 0 don't reflect

	return newUpgrade;
}

void moveUpgrade(Upgrade* thisUpgrade, double dt) {
	thisUpgrade->speed[0] += thisUpgrade->acceleration[0] * dt;
	thisUpgrade->speed[1] += thisUpgrade->acceleration[1] * dt;
	thisUpgrade->x += thisUpgrade->speed[0] * dt;
	thisUpgrade->y += thisUpgrade->speed[1] * dt;
}

void renderUpgrade(Upgrade* thisUpgrade, double lag) {
	renderCircle(thisUpgrade, lag);
}

void destroyUpgrade(Upgrade** thisUpgrade) {
	free((*thisUpgrade)->userParam);
	destroyCircle(thisUpgrade);
}