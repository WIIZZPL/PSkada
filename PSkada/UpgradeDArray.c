#include "UpgradeDArray.h"

void shrinkUpgradeDArray(UpgradeDArray* thisUpgradeDArray);

UpgradeDArray* createUpgradeDArray() {
	UpgradeDArray* newUpgradeDArray = (UpgradeDArray*)malloc(sizeof(UpgradeDArray));
	if (!newUpgradeDArray) exit(138);
	newUpgradeDArray->size = 0;
	newUpgradeDArray->capacity = 1;
	newUpgradeDArray->arr = (Upgrade**)calloc(1, sizeof(Upgrade*));
	if (!newUpgradeDArray->arr) exit(138);
	return newUpgradeDArray;
}

void appendUpgradeDArray(UpgradeDArray* thisUpgradeDArray, Upgrade* upgrade) {
	if (thisUpgradeDArray->size == thisUpgradeDArray->capacity) {
		thisUpgradeDArray->capacity *= 2;
		thisUpgradeDArray->arr = (Upgrade**)realloc(thisUpgradeDArray->arr, thisUpgradeDArray->capacity * sizeof(Upgrade*));
		if (!thisUpgradeDArray->arr) exit(138);
	}
	thisUpgradeDArray->arr[thisUpgradeDArray->size++] = upgrade;
}

void removeUpgradeDArray(UpgradeDArray* thisUpgradeDArray, Upgrade** Upgrade) {
	destroyUpgrade(Upgrade);
	unsigned int index = Upgrade - thisUpgradeDArray->arr;
	for (unsigned int i = index; i < thisUpgradeDArray->size; i++) {
		thisUpgradeDArray->arr[i] = thisUpgradeDArray->arr[i + 1];
	}
	thisUpgradeDArray->size--;
	//shrinkUpgradeDArray(thisUpgradeDArray);
}

void shrinkUpgradeDArray(UpgradeDArray* thisUpgradeDArray) {
	if (thisUpgradeDArray->capacity / 2 > thisUpgradeDArray->size) {
		thisUpgradeDArray->capacity /= 2;
		thisUpgradeDArray->arr = (Upgrade**)realloc(thisUpgradeDArray->arr, thisUpgradeDArray->capacity);
		if (!thisUpgradeDArray->arr) exit(138);
	}
}

void moveUpgradeDArray(UpgradeDArray* thisUpgradeDArray, double dt) {
	for (unsigned int i = 0; i < thisUpgradeDArray->size; i++) {
		moveUpgrade(thisUpgradeDArray->arr[i], dt);
	}
}

void renderUpgradeDArray(UpgradeDArray* thisUpgradeDArray, double lag) {
	for (unsigned int i = 0; i < thisUpgradeDArray->size; i++) {
		renderUpgrade(thisUpgradeDArray->arr[i], lag);
	}
}

void destroyUpgradeDArray(UpgradeDArray** thisUpgradeDArray) {
	if (!*thisUpgradeDArray) return;
	for (unsigned int i = 0; i < (*thisUpgradeDArray)->size; i++) destroyUpgrade((*thisUpgradeDArray)->arr + i);
	free((*thisUpgradeDArray)->arr);
	free(*thisUpgradeDArray);
	*thisUpgradeDArray = NULL;
}