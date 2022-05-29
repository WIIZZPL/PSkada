#pragma once

#include "Upgrade.h"

typedef struct UpgradeDArray {
	unsigned int size;
	unsigned int capacity;
	Upgrade** arr;
} UpgradeDArray;

UpgradeDArray* createUpgradeDArray();

void appendUpgradeDArray(UpgradeDArray* thisUpgradeDArray, Upgrade* upgrade);
void removeUpgradeDArray(UpgradeDArray* thisUpgradeDArray, Upgrade** upgrade);
void shrinkUpgradeDArray(UpgradeDArray* thisUpgradeDArray);

void updateUpgradeDArray(UpgradeDArray* thisUpgradeDArray, double dt);
void renderUpgradeDArray(UpgradeDArray* thisUpgradeDArray, double lag);

void destroyUpgradeDArray(UpgradeDArray** thisUpgradeDArray);