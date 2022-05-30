#pragma once

#include "Brick.h"
#include "BrickDArray.h"
#include <allegro5/allegro_primitives.h>

#define BRICK_QTREE_CAP 4

typedef struct BrickQTree {
	float x, y, w, h;
	int size;
	Brick*** bricks;
	struct BrickQTree** subdivs;
} BrickQTree;

BrickQTree* createBrickQTree(float x, float y, float w, float h);

void subdevideBrickQTree(BrickQTree* thisBrickQTree);
int isSubdivedBrickQTree(BrickQTree* thisBrickQTree);
void insertBrickQTree(BrickQTree* thisBrickQTree, Brick** brick);

void destroyBrickQTree(BrickQTree** thisBrickQTree);

void renderBrickQTree(BrickDArray* bricks, float x, float y, float w, float h);