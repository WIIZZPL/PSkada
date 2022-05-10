#pragma once

#include "Brick.h"
#include "BrickDArray.h"

#define BrickQTreeCapacity 4

typedef struct BrickQTree {
	float x, y, w, h;
	int size;
	Brick*** bricks;
	struct BrickQTree** subdivs;
} BrickQTree;

BrickQTree* createBrickQTree(float x, float y, float w, float h);
Brick* copyBrick(Brick* brick);

void subdevideBrickQTree(BrickQTree* thisBrickQTree);
int isSubdivedBrickQTree(BrickQTree* thisBrickQTree);
void insertBrickQTree(BrickQTree* thisBrickQTree, Brick** brick);
void clearBrickQTree(BrickQTree* thisBrickQTree);

void destroyBrickQTree(BrickQTree** thisBrickQTree);

void renderBrickQTree(BrickQTree* thisBrickQTree);