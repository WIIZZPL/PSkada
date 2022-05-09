#pragma once

#include "rectangle.h"
#define BrickQTreeCapacity 4

typedef Rectangle Brick;

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp);

void renderBrick(Brick* thisBrick);

void destroyBrick(Brick** thisBrick);

typedef struct BrickQTree {
	float x, y, w, h;
	int size;
	Brick** bricks;
	struct BrickQTree** subdivs;
} BrickQTree;

BrickQTree* createBrickQTree(float x, float y, float w, float h);
Brick* copyBrick(Brick* brick);

void subdevideBrickQTree(BrickQTree* thisBrickQTree);
int isSubdivedBrickQTree(BrickQTree* thisBrickQTree);
void insertBrickQTree(BrickQTree* thisBrickQTree, Brick* brick);

void destroyBrickQTree(BrickQTree** thisBrickQTree);

void renderBrickQTree(BrickQTree* thisBrickQTree);