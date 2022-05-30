#include "Ball.h"

Ball* createBall(float x, float y, float speedX, float speedY, double penetrationTimer) {
	float ballSpeed[2] = { speedX, speedY };
	float ballAcceleration[2] = { 0, 0 };

	ALLEGRO_BITMAP* bmp = al_load_bitmap("ball.png");

	Ball* newBall = createCircle(x, y, BALL_RADIUS, ballSpeed, ballAcceleration, bmp);
	if (!newBall) exit(138);

	newBall->userParam = (double*)malloc(sizeof(double));
	if (!newBall->userParam) exit(138);
	*(double*)newBall->userParam = penetrationTimer; //Penetration timer, if <=0 reflect

	return newBall;
}

void moveBall(Ball* thisBall, double dt) {
	thisBall->x += thisBall->speed[0] * dt;
	thisBall->y += thisBall->speed[1] * dt;
	*(double*)thisBall->userParam -= dt;
}

void renderBall(Ball* thisBall, double lag) {
	renderCircle(thisBall, lag);
}

void destroyBall(Ball** thisBall) {
	free((double*)(*thisBall)->userParam);
	destroyCircle(thisBall);
}