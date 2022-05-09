#include "Brick.h"
#include <stdio.h>
int brickCount;
int qtreeCount;
int insertedBricks;

Brick* createBrick(float x, float y, float w, float h, ALLEGRO_BITMAP* bmp) {
	Brick* ptr = createRectangle(x, y, w, h, bmp);
	printf("Brick Created! %x (%d)\n", ptr, ++brickCount);
	return ptr;
}

Brick* copyBrick(Brick* brick) {
	printf("Brick Copied! %x (%d)\n", brick, ++brickCount);
	return copyRectangle(brick);
}

void renderBrick(Brick* thisBrick) {
	if (!thisBrick) return;
	renderRectangle(thisBrick);
}

void destroyBrick(Brick** thisBrick) {
	printf("Brick Destroyed! %x (%d)\n", *thisBrick, --brickCount);
	destroyRectangle(thisBrick);
}

BrickQTree* createBrickQTree(float x, float y, float w, float h) {
	BrickQTree* newBrickQTree = (BrickQTree*)malloc(sizeof(BrickQTree));
	if (!newBrickQTree) exit(138);
	newBrickQTree->x = x;
	newBrickQTree->y = y;
	newBrickQTree->w = w;
	newBrickQTree->h = h;
	newBrickQTree->size = 0;
	newBrickQTree->bricks = calloc(BrickQTreeCapacity, sizeof(Brick*));
	newBrickQTree->subdivs = NULL;
	printf("QTree Created! (%d)\n", ++qtreeCount);
	return newBrickQTree;
}

void subdevideBrickQTree(BrickQTree* thisBrickQTree) {
	printf("Splitting!\n");
	thisBrickQTree->subdivs = calloc(4, sizeof(BrickQTree*));
	if (!thisBrickQTree->subdivs) exit(138);
	//Creating sub trees
	float x = thisBrickQTree->x;
	float y = thisBrickQTree->y;
	float w = thisBrickQTree->w;
	float h = thisBrickQTree->h;
	thisBrickQTree->subdivs[0] = createBrickQTree(x,     y,     w / 2, h / 2); //North-west
	thisBrickQTree->subdivs[1] = createBrickQTree(x+w/2, y,     w / 2, h / 2); //North-east
	thisBrickQTree->subdivs[2] = createBrickQTree(x,     y+h/2, w / 2, h / 2); //South-west
	thisBrickQTree->subdivs[3] = createBrickQTree(x+w/2, y+h/2, w / 2, h / 2); //South-east
	//Inserting bricks into sub tress then removing
	for (int i = 0; i < thisBrickQTree->size; i++) {
		insertBrickQTree(thisBrickQTree->subdivs[0], copyBrick(thisBrickQTree->bricks[i]));
		insertBrickQTree(thisBrickQTree->subdivs[1], copyBrick(thisBrickQTree->bricks[i]));
		insertBrickQTree(thisBrickQTree->subdivs[2], copyBrick(thisBrickQTree->bricks[i]));
		insertBrickQTree(thisBrickQTree->subdivs[3], copyBrick(thisBrickQTree->bricks[i]));
		//destroyBrick(thisBrickQTree->bricks + i);
	}
	free(thisBrickQTree->bricks);
	thisBrickQTree->bricks = NULL;
}

int isSubdivedBrickQTree(BrickQTree* thisBrickQTree) {
	return thisBrickQTree->subdivs != NULL;
}

void insertBrickQTree(BrickQTree* thisBrickQTree, Brick* brick) {
	//Check if brick in QTree bounds
	if ((thisBrickQTree->x + thisBrickQTree->w < brick->x || thisBrickQTree->x > brick->x + brick->w) ||
		(thisBrickQTree->y + thisBrickQTree->h < brick->y || thisBrickQTree->y > brick->y + brick->h)) {
		//destroyBrick(&brick);
		return;
	}
	printf("Inserting brick! (%d)\n\n", ++insertedBricks);
	//Insertion part proper
	if (thisBrickQTree->size < BrickQTreeCapacity) {
		thisBrickQTree->bricks[thisBrickQTree->size++] = brick;
	}
	else {
		if (!isSubdivedBrickQTree(thisBrickQTree)) subdevideBrickQTree(thisBrickQTree);
		insertBrickQTree(thisBrickQTree->subdivs[0], brick);
		insertBrickQTree(thisBrickQTree->subdivs[1], brick);
		insertBrickQTree(thisBrickQTree->subdivs[2], brick);
		insertBrickQTree(thisBrickQTree->subdivs[3], brick);
	}
}

void destroyBrickQTree(BrickQTree** thisBrickQTree) {
	if (!*thisBrickQTree) return;

	if (isSubdivedBrickQTree(*thisBrickQTree)) {
		destroyBrickQTree((*thisBrickQTree)->subdivs);
		destroyBrickQTree((*thisBrickQTree)->subdivs + 1);
		destroyBrickQTree((*thisBrickQTree)->subdivs + 2);
		destroyBrickQTree((*thisBrickQTree)->subdivs + 3);
		free((*thisBrickQTree)->subdivs);
	}
	else {
		for (int i = 0; i < (*thisBrickQTree)->size; i++) {
			destroyBrick((*thisBrickQTree)->bricks + i);
		}
		free((*thisBrickQTree)->bricks);
	}

	free(*thisBrickQTree);
	*thisBrickQTree = NULL;
	printf("QTree Destroyed! (%d)\n", --qtreeCount);
}
#include <allegro5/allegro_primitives.h>
void renderBrickQTree(BrickQTree* thisBrickQTree) {
	if (isSubdivedBrickQTree(thisBrickQTree)) {
		renderBrickQTree(thisBrickQTree->subdivs[0]);
		renderBrickQTree(thisBrickQTree->subdivs[1]);
		renderBrickQTree(thisBrickQTree->subdivs[2]);
		renderBrickQTree(thisBrickQTree->subdivs[3]);
	}
	else {
		for (int i = 0; i < thisBrickQTree->size; i++) renderBrick(thisBrickQTree->bricks[i]);
	}
	al_draw_rectangle((thisBrickQTree->x)*displayWidth, (thisBrickQTree->y)*displayHeight,
		(thisBrickQTree->x + thisBrickQTree->w)*displayWidth, (thisBrickQTree->y + thisBrickQTree->h)*displayHeight,
		al_map_rgb(255, 255, 255), 1);
}