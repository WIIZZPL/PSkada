#pragma once

#include "Brick.h"

typedef struct BrickDArray {
	unsigned int size;
	unsigned int capacity;
	Brick** arr;
} BrickDArray;

BrickDArray* createBrickDArray();

void appendBrickDArray(BrickDArray* thisBrickDArray, Brick* brick);
void removeBrickDArray(BrickDArray* thisBrickDArray, Brick** brick);

void renderBrickDArray(BrickDArray* thisBrickDArray);

void destroyBrickDArray(BrickDArray** thisBrickDArray);