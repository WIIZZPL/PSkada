#include "Ball.h"

Ball* createBall(float x, float y, float r, ALLEGRO_BITMAP* bmp) {
	float ballSpeed[2] = { 0.3, 0.15 };
	float ballAcceleration[2] = { 0, 0 };

	Ball* newBall = createCircle(x, y, r, ballSpeed, ballAcceleration, bmp);
	if (!newBall) exit(138);

	newBall->userParam = (char*)malloc(sizeof(char));
	if (!newBall->userParam) exit(138);
	*(char*)newBall->userParam = 1; //Non-Penetrating. if 0 don't reflect

	return newBall;
}

void updateBall(Ball** thisBall, Palette* palette, BrickDArray* bricks, BrickQTree* bricksQTree, UpgradeDArray* upgrades, double dt) {
	
	//MOVEMENT
	(*thisBall)->x += (*thisBall)->speed[0] * dt;
	(*thisBall)->y += (*thisBall)->speed[1] * dt;
	
	//BOUNDING BOX COLLISION
	if ((*thisBall)->x + (*thisBall)->r > 1 || (*thisBall)->x - (*thisBall)->r < 0) {
		(*thisBall)->speed[0] *= -1;
		max((*thisBall)->r, (*thisBall)->x);
		min(1 - (*thisBall)->r, (*thisBall)->x);
	}
	//if ((*thisBall)->y + (*thisBall)->r > 1) {
	//	destroyBall(thisBall);
	//	return;
	//}
	if ((*thisBall)->y + (*thisBall)->r > 1 || (*thisBall)->y - (*thisBall)->r < 0) {
		(*thisBall)->speed[1] *= -1;
		max((*thisBall)->r, (*thisBall)->y);
		min(1 - (*thisBall)->r, (*thisBall)->y);
	}

	//PALETTE COLLISION
	//nearest point on the palette to the circle
	{
		float nx = max(palette->x, min(palette->x + palette->w, (*thisBall)->x));
		float ny = max(palette->y, min(palette->y + palette->h, (*thisBall)->y));
		if (powf(fabsf(nx - (*thisBall)->x), 2) + powf(fabsf(ny - (*thisBall)->y), 2) <= powf((*thisBall)->r,2)) {
			float paletteCurvature = 0.5;
			float b = -paletteCurvature * 0.5 + 0.5;
			float collisionAngle = ((nx-palette->x)/palette->w)*paletteCurvature+b;
			float speedMagnitude = sqrt((*thisBall)->speed[0] * (*thisBall)->speed[0] + (*thisBall)->speed[1] * (*thisBall)->speed[1]);

			(*thisBall)->speed[0] = speedMagnitude*-(cos(collisionAngle * 3.1415));
			(*thisBall)->speed[1] = speedMagnitude*-(sin(collisionAngle * 3.1415));
		}
	}

	//BRICK COLLISION
	//Possibly coliding brick
	brickQTreeBallColission(*thisBall, bricks, bricksQTree, upgrades);
}

void brickQTreeBallColission(Ball* thisBall, BrickDArray* bricks, BrickQTree* bricksQTree, UpgradeDArray* upgrades) {
	float QTnx = max(bricksQTree->x, min(bricksQTree->x + bricksQTree->w, thisBall->x));
	float QTny = max(bricksQTree->y, min(bricksQTree->y + bricksQTree->h, thisBall->y));
	if (powf(fabsf(QTnx - thisBall->x), 2) + powf(fabsf(QTny - thisBall->y), 2) <= powf(thisBall->r, 2)) {
		if (isSubdivedBrickQTree(bricksQTree)) {
			brickQTreeBallColission(thisBall, bricks, bricksQTree->subdivs[0], upgrades);
			brickQTreeBallColission(thisBall, bricks, bricksQTree->subdivs[1], upgrades);
			brickQTreeBallColission(thisBall, bricks, bricksQTree->subdivs[2], upgrades);
			brickQTreeBallColission(thisBall, bricks, bricksQTree->subdivs[3], upgrades);
		}
		else {
			for (int i = 0; i < bricksQTree->size; i++) {
				Brick** brick = bricksQTree->bricks[i];
				float nx = max((*brick)->x, min((*brick)->x + (*brick)->w, thisBall->x));
				float ny = max((*brick)->y, min((*brick)->y + (*brick)->h, thisBall->y));
				if (powf(fabsf(nx - thisBall->x), 2) + powf(fabsf(ny - thisBall->y), 2) <= powf(thisBall->r, 2)) {
					if (*(char*)thisBall->userParam & (nx == (*brick)->x || nx == (*brick)->x + (*brick)->w)) {
						thisBall->speed[0] *= -1;
					}
					if (*(char*)thisBall->userParam & (ny == (*brick)->y || ny == (*brick)->y + (*brick)->h)) {
						thisBall->speed[1] *= -1;
					}
					if((float)rand()/RAND_MAX <= 1.10) appendUpgradeDArray(upgrades, createUpgrade( (*brick)->x + (*brick)->w/2, (*brick)->y + ((*brick)->h)/2));
					removeBrickDArray(bricks, brick);
					return;
				}
			}
		}
	}
}

void renderBall(Ball* thisBall, double lag) {
	renderCircle(thisBall, lag);
}

void destroyBall(Ball** thisBall) {
	free((*thisBall)->userParam);
	destroyCircle(thisBall);
}