#include "BrickDArray.h"

BrickDArray* createBrickDArray() {
	BrickDArray* newBrickDArray = (BrickDArray*)malloc(sizeof(BrickDArray));
	if (!newBrickDArray) exit(138);
	newBrickDArray->size = 0;
	newBrickDArray->capacity = 1;
	newBrickDArray->arr = (Brick**)calloc(1, sizeof(Brick*));
	if (!newBrickDArray->arr) exit(138);
	return newBrickDArray;
}

void appendBrickDArray(BrickDArray* thisBrickDArray, Brick* brick) {
	if (thisBrickDArray->size == thisBrickDArray->capacity) {
		thisBrickDArray->capacity *= 2;
		thisBrickDArray->arr = (Brick**)realloc(thisBrickDArray->arr, thisBrickDArray->capacity*sizeof(Brick*));
		if (!thisBrickDArray->arr) exit(138);
	}
	thisBrickDArray->arr[thisBrickDArray->size++] = brick;
}

void removeBrickDArray(BrickDArray* thisBrickDArray, Brick** brick) {
	destroyBrick(brick);
	unsigned int index = brick-thisBrickDArray->arr;
	for (unsigned int i = index; i < thisBrickDArray->size; i++) {
		thisBrickDArray->arr[i] = thisBrickDArray->arr[i + 1];
	}
	thisBrickDArray->size--;
}

void shrinkBrickDArray(BrickDArray* thisBrickDArray) {
	if (thisBrickDArray->capacity / 2 > thisBrickDArray->size) {
		thisBrickDArray->capacity /= 2;
		thisBrickDArray->arr = (Brick**)realloc(thisBrickDArray->arr, thisBrickDArray->capacity);
		if (!thisBrickDArray->arr) exit(138);
	}
}
#include <stdio.h>
void renderBrickDArray(BrickDArray* thisBrickDArray) {
	for (unsigned int i = 0; i < thisBrickDArray->size; i++) {
		renderBrick(thisBrickDArray->arr[i]);
	}
}

void destroyBrickDArray(BrickDArray** thisBrickDArray) {
	if (!*thisBrickDArray) return;
	for (unsigned int i = 0; i < (*thisBrickDArray)->size; i++) destroyBrick((*thisBrickDArray)->arr + i);
	free((*thisBrickDArray)->arr);
	free(*thisBrickDArray);
	*thisBrickDArray = NULL;
}