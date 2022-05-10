#include "BrickQTree.h"

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
	return newBrickQTree;
}

void subdevideBrickQTree(BrickQTree* thisBrickQTree) {
	thisBrickQTree->subdivs = calloc(4, sizeof(BrickQTree*));
	if (!thisBrickQTree->subdivs) exit(138);
	//Creating sub trees
	float x = thisBrickQTree->x;
	float y = thisBrickQTree->y;
	float w = thisBrickQTree->w;
	float h = thisBrickQTree->h;
	thisBrickQTree->subdivs[0] = createBrickQTree(x,         y,         w / 2, h / 2); //North-west
	thisBrickQTree->subdivs[1] = createBrickQTree(x + w / 2, y,         w / 2, h / 2); //North-east
	thisBrickQTree->subdivs[2] = createBrickQTree(x,         y + h / 2, w / 2, h / 2); //South-west
	thisBrickQTree->subdivs[3] = createBrickQTree(x + w / 2, y + h / 2, w / 2, h / 2); //South-east
	//Inserting bricks into sub tress then removing
	for (int i = 0; i < thisBrickQTree->size; i++) {
		insertBrickQTree(thisBrickQTree->subdivs[0], thisBrickQTree->bricks[i]);
		insertBrickQTree(thisBrickQTree->subdivs[1], thisBrickQTree->bricks[i]);
		insertBrickQTree(thisBrickQTree->subdivs[2], thisBrickQTree->bricks[i]);
		insertBrickQTree(thisBrickQTree->subdivs[3], thisBrickQTree->bricks[i]);
	}
	free(thisBrickQTree->bricks);
	thisBrickQTree->bricks = NULL;
}

int isSubdivedBrickQTree(BrickQTree* thisBrickQTree) {
	return thisBrickQTree->subdivs != NULL;
}

void insertBrickQTree(BrickQTree* thisBrickQTree, Brick** brick) {
	//Check if brick in QTree bounds
	if ((thisBrickQTree->x + thisBrickQTree->w < (*brick)->x || thisBrickQTree->x > (*brick)->x + (*brick)->w) ||
		(thisBrickQTree->y + thisBrickQTree->h < (*brick)->y || thisBrickQTree->y > (*brick)->y + (*brick)->h)) {
		return;
	}
	//Insertion part proper
	if (thisBrickQTree->size < BrickQTreeCapacity && thisBrickQTree->bricks != NULL) {
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

void clearBrickQTree(BrickQTree* thisBrickQTree) {
	if (isSubdivedBrickQTree(thisBrickQTree)) {
		destroyBrickQTree(thisBrickQTree->subdivs+0);
		destroyBrickQTree(thisBrickQTree->subdivs+1);
		destroyBrickQTree(thisBrickQTree->subdivs+2);
		destroyBrickQTree(thisBrickQTree->subdivs+3);
		free(thisBrickQTree->subdivs);
		thisBrickQTree->subdivs = NULL;
	}
	else{
		for (int i = 0; i < thisBrickQTree->size; i++) {
			thisBrickQTree->bricks[i] = NULL;
		}
	}
	thisBrickQTree->size = 0;
}

void destroyBrickQTree(BrickQTree** thisBrickQTree) {
	if (!*thisBrickQTree) return;
	clearBrickQTree(*thisBrickQTree);
	free((*thisBrickQTree)->bricks);
	free(*thisBrickQTree);
	*thisBrickQTree = NULL;
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
		for (int i = 0; i < thisBrickQTree->size; i++) renderBrick(*thisBrickQTree->bricks[i]);
	}
	al_draw_rectangle((thisBrickQTree->x) * displayWidth, (thisBrickQTree->y) * displayHeight,
		(thisBrickQTree->x + thisBrickQTree->w) * displayWidth, (thisBrickQTree->y + thisBrickQTree->h) * displayHeight,
		al_map_rgb(255, 255, 255), 1);
}