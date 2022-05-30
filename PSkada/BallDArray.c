#include "BallDArray.h"

void shrinkBallDArray(BallDArray* thisBallDArray);

BallDArray* createBallDArray() {
	BallDArray* newBallDArray = (BallDArray*)malloc(sizeof(BallDArray));
	if (!newBallDArray) exit(138);
	newBallDArray->size = 0;
	newBallDArray->capacity = 1;
	newBallDArray->arr = (Ball**)calloc(1, sizeof(Ball*));
	if (!newBallDArray->arr) exit(138);
	return newBallDArray;
}

void appendBallDArray(BallDArray* thisBallDArray, Ball* ball) {
	if (thisBallDArray->size == thisBallDArray->capacity) {
		thisBallDArray->capacity *= 2;
		thisBallDArray->arr = (Ball**)realloc(thisBallDArray->arr, thisBallDArray->capacity * sizeof(Ball*));
		if (!thisBallDArray->arr) exit(138);
	}
	thisBallDArray->arr[thisBallDArray->size++] = ball;
}

void removeBallDArray(BallDArray* thisBallDArray, Ball** ball) {
	destroyBall(ball);
	unsigned int index = ball - thisBallDArray->arr;
	for (unsigned int i = index; i < thisBallDArray->size; i++) {
		thisBallDArray->arr[i] = thisBallDArray->arr[i + 1];
	}
	thisBallDArray->size--;
	//shrinkBallDArray(thisBallDArray);
}

void shrinkBallDArray(BallDArray* thisBallDArray) {
	if (thisBallDArray->capacity / 2 >= thisBallDArray->size) {
		thisBallDArray->capacity /= 2;
		thisBallDArray->arr = (Ball**)realloc(thisBallDArray->arr, thisBallDArray->capacity);
		if (!thisBallDArray->arr) exit(138);
	}
}

void moveBallDArray(BallDArray* thisBallDArray, double dt) {
	for (unsigned int i = 0; i < thisBallDArray->size; i++) {
		moveBall(thisBallDArray->arr[i], dt);
	}
}

void renderBallDArray(BallDArray* thisBallDArray, double lag) {
	for (unsigned int i = 0; i < thisBallDArray->size; i++) {
		renderBall(thisBallDArray->arr[i], lag);
	}
}

void destroyBallDArray(BallDArray** thisBallDArray) {
	if (!*thisBallDArray) return;
	for (unsigned int i = 0; i < (*thisBallDArray)->size; i++) destroyBall((*thisBallDArray)->arr + i);
	free((*thisBallDArray)->arr);
	free(*thisBallDArray);
	*thisBallDArray = NULL;
}