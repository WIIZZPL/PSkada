#pragma once

#include "Ball.h"

typedef struct BallDArray {
	unsigned int size;
	unsigned int capacity;
	Ball** arr;
} BallDArray;

BallDArray* createBallDArray();

void appendBallDArray(BallDArray* thisBallDArray, Ball* Ball);
void removeBallDArray(BallDArray* thisBallDArray, Ball** Ball);

void moveBallDArray(BallDArray* thisBallDArray, double dt);
void renderBallDArray(BallDArray* thisBallDArray, double lag);

void destroyBallDArray(BallDArray** thisBallDArray);