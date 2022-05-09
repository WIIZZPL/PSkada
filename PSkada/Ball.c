#include "Ball.h"

Ball* createBall(float x, float y, float r, ALLEGRO_BITMAP* bmp) {
	float ballSpeed[2] = { 0.3, 0.15 };
	float ballAcceleration[2] = { 0, 0 };

	Ball* newBall = createCircle(x, y, r, ballSpeed, ballAcceleration, bmp);
	if (!newBall) exit(138);
	return newBall;
}

void updateBall(Ball** thisBall, Palette* palette, Brick** brick, double dt) {
	(*thisBall)->x += (*thisBall)->speed[0] * dt;
	(*thisBall)->y += (*thisBall)->speed[1] * dt;
	
	//BOUNDING BOX COLLISION
	if ((*thisBall)->x + (*thisBall)->r > 1 || (*thisBall)->x - (*thisBall)->r < 0) {
		(*thisBall)->speed[0] *= -1;
		max((*thisBall)->r, (*thisBall)->x);
		min(1 - (*thisBall)->r, (*thisBall)->x);
	}
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
	/*if (*brick) {
		float nx = max((*brick)->x, min((*brick)->x + (*brick)->w, (*thisBall)->x));
		float ny = max((*brick)->y, min((*brick)->y + (*brick)->h, (*thisBall)->y));
		if (powf(fabsf(nx - (*thisBall)->x), 2) + powf(fabsf(ny - (*thisBall)->y), 2) <= powf((*thisBall)->r, 2)) {
			if (nx == (*brick)->x || nx == (*brick)->x + (*brick)->w) {
				(*thisBall)->speed[0] *= -1;
			}
			else {
				(*thisBall)->speed[1] *= -1;
			}
			destroyBrick(brick);
		}
	}*/
}

void renderBall(Ball* thisBall, double lag) {
	renderCircle(thisBall, lag);
}

void destroyBall(Ball** thisBall) {
	destroyCircle(thisBall);
}