#pragma once

#include "circle.h"

typedef Circle Ball;

#define BALL_RADIUS (1.0/128)

Ball* createBall(float x, float y, float speedX, float speedY, double penetrationTimer);

void moveBall(Ball* thisBall, double dt);
void renderBall(Ball* thisBall, double lag);

void destroyBall(Ball** thisBall);