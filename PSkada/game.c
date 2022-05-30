#include "game.h"

char keyboardState[ALLEGRO_KEY_MAX];

Palette* palette;
BallDArray* balls;
UpgradeDArray* upgrades;
BrickDArray* bricks;

void handleColissions(Palette* palette, BallDArray* balls, UpgradeDArray* upgrades, BrickDArray* bricks);
int rectangleCircleColission(Rectangle* thisRectangle, Circle* thisCircle);
void brickQTreeBallColission(BrickQTree* bricksQTree, BrickDArray* bricks, Ball* thisBall, UpgradeDArray* upgrades);
void executeUpgrade(char upCode, Palette* palette, BallDArray* balls);

void game_init() {
	srand(time(NULL));
	
	palette = createPalette(6.0 / 16, 8.5 / 9, 4.0 / 16, 0.25 / 9);
	
	balls = createBallDArray();
	appendBallDArray(balls, createBall(0.5, 0.5, 0.3, 0.3, 0.0));

	upgrades = createUpgradeDArray();

	bricks = createBrickDArray();
	appendBrickDArray(bricks, createBrick(0.5 / 16, 0.5 / 9));
	appendBrickDArray(bricks, createBrick(2.5 / 16, 0.5 / 9));
	appendBrickDArray(bricks, createBrick(4.5 / 16, 0.5 / 9));
	appendBrickDArray(bricks, createBrick(4.5 / 16, 1.5 / 9));
	appendBrickDArray(bricks, createBrick(2.5 / 16, 1.5 / 9));
	appendBrickDArray(bricks, createBrick(12.5/ 16, 5.5 / 9));
}

void game_processImput(ALLEGRO_EVENT* event) {
	//Rejestrowanie wcisniecia klawiszy; (bitowo) 11 - wcisniety, 10 - odcisniety nie zarejestrowany, 01 - wcisniety zarejestrowany.
	if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
		keyboardState[event->keyboard.keycode] = 3;
	}
	else if (event->type == ALLEGRO_EVENT_KEY_UP) {
		keyboardState[event->keyboard.keycode] = keyboardState[event->keyboard.keycode] ^ 1;
		if (event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) switchScenes(0);
	}
}

void game_update(double t, double dt) {
	movePalette(palette, dt, keyboardState);
	moveBallDArray(balls, dt);
	moveUpgradeDArray(upgrades, dt);
	handleColissions(palette, balls, upgrades, bricks);
}

void game_render(ALLEGRO_DISPLAY* display, double lag) {
	al_draw_filled_rectangle(displayX, displayY, displayX + displayWidth, displayY + displayHeight, al_map_rgb(38, 0, 83));
	renderPalette(palette);
	renderBallDArray(balls, lag);
	renderUpgradeDArray(upgrades, lag);
	renderBrickDArray(bricks);
}

void game_del() {
	destroyPalette(&palette);
	destroyBallDArray(&balls);
	destroyUpgradeDArray(&upgrades);
	destroyBrickDArray(&bricks);
}

void handleColissions(Palette* palette, BallDArray* balls, UpgradeDArray* upgrades, BrickDArray* bricks) {
	// Palette bounding box
	palette->x = fmax(GAME_BOUNDBOX_X, fmin(GAME_BOUNDBOX_X+GAME_BOUNDBOX_WIDTH-palette->w, palette->x));

	// Balls
	BrickQTree* bricksQTree = createBrickQTree(GAME_BOUNDBOX_X, GAME_BOUNDBOX_Y, GAME_BOUNDBOX_WIDTH, GAME_BOUNDBOX_HEIGHT);
	for (unsigned int i = 0; i < bricks->size; i++) insertBrickQTree(bricksQTree, bricks->arr + i);

	for (unsigned int i = 0; i < balls->size; i++) {
		Ball* ball = balls->arr[i];

		//Bounding box
		if (ball->x <= GAME_BOUNDBOX_X + ball->r || ball->x >= GAME_BOUNDBOX_X + GAME_BOUNDBOX_WIDTH - ball->r) ball->speed[0] *= -1;
		if (ball->y <= GAME_BOUNDBOX_Y + ball->r) ball->speed[1] *= -1;
		if (ball->y >= GAME_BOUNDBOX_Y + GAME_BOUNDBOX_HEIGHT - ball->r) {
			removeBallDArray(balls, balls->arr + i);
			continue;
		}

		//Palette
		if (rectangleCircleColission(palette, ball)) {
			float paletteCurvature = 0.5;
			float b = -paletteCurvature * 0.5 + 0.5;
			float nx = max(palette->x, min(palette->x + palette->w, ball->x));
			float collisionAngle = ((nx - palette->x) / palette->w) * paletteCurvature + b;
			float speedMagnitude = sqrt(ball->speed[0] * ball->speed[0] + ball->speed[1] * ball->speed[1]);

			ball->speed[0] = speedMagnitude * -(cos(collisionAngle * 3.1415));
			ball->speed[1] = speedMagnitude * -(sin(collisionAngle * 3.1415));
		}

		//Bricks
		brickQTreeBallColission(bricksQTree, bricks, ball, upgrades);
	}
	
	destroyBrickQTree(&bricksQTree);
	
	// Upgrades
	for (unsigned int i = 0; i < upgrades->size; i++) {
		Upgrade* upgrade = upgrades->arr[i];

		//Bounding box
		if (upgrade->x <= GAME_BOUNDBOX_X - upgrade->r || upgrade->x >= GAME_BOUNDBOX_X + GAME_BOUNDBOX_WIDTH + upgrade->r ||
			upgrade->y <= GAME_BOUNDBOX_Y - upgrade->r || upgrade->y >= GAME_BOUNDBOX_Y + GAME_BOUNDBOX_HEIGHT + upgrade->r) {
			removeUpgradeDArray(upgrades, upgrades->arr + i);
			continue;
		}
		

		//Palette
		if (rectangleCircleColission(palette, upgrade)) {
			executeUpgrade(*(char*)upgrade->userParam, palette, balls);
			removeUpgradeDArray(upgrades, upgrades->arr + i);
			continue;
		}
	}
}

int rectangleCircleColission(Rectangle* thisRectangle, Circle* thisCircle) {
	float nx = max(thisRectangle->x, min(thisRectangle->x + thisRectangle->w, thisCircle->x));
	float ny = max(thisRectangle->y, min(thisRectangle->y + thisRectangle->h, thisCircle->y));
	return (powf(fabsf(nx - thisCircle->x), 2) + powf(fabsf(ny - thisCircle->y), 2) <= powf(thisCircle->r, 2));
}

void brickQTreeBallColission(BrickQTree* bricksQTree, BrickDArray* bricks, Ball* thisBall, UpgradeDArray* upgrades) {
	float nx = max(bricksQTree->x, min(bricksQTree->x + bricksQTree->w, thisBall->x));
	float ny = max(bricksQTree->y, min(bricksQTree->y + bricksQTree->h, thisBall->y));
	if (!(powf(fabsf(nx - thisBall->x), 2) + powf(fabsf(ny - thisBall->y), 2) <= powf(thisBall->r, 2))) return;

	if (isSubdivedBrickQTree(bricksQTree)) {
		brickQTreeBallColission(bricksQTree->subdivs[0], bricks, thisBall, upgrades);
		brickQTreeBallColission(bricksQTree->subdivs[1], bricks, thisBall, upgrades);
		brickQTreeBallColission(bricksQTree->subdivs[2], bricks, thisBall, upgrades);
		brickQTreeBallColission(bricksQTree->subdivs[3], bricks, thisBall, upgrades);
	} else {
		for (int i = 0; i < bricksQTree->size; i++) {
			Brick* brick = *bricksQTree->bricks[i];
			if (!brick) continue;
			nx = max(brick->x, min(brick->x + brick->w, thisBall->x));
			ny = max(brick->y, min(brick->y + brick->h, thisBall->y));
			if (powf(fabsf(nx - thisBall->x), 2) + powf(fabsf(ny - thisBall->y), 2) <= powf(thisBall->r, 2)) {

				if (*(double*)thisBall->userParam <= 0.0) {
					if (nx == brick->x || nx == brick->x + brick->w) thisBall->speed[0] *= -1;
					if (ny == brick->y || ny == brick->y + brick->h) thisBall->speed[1] *= -1;
				}
				
				if(rand()/RAND_MAX <= 0.1) appendUpgradeDArray(upgrades, createUpgrade(brick->x + brick->w / 2, brick->y + brick->h / 2));
				
				removeBrickDArray(bricks, bricksQTree->bricks[i]);
				return;
			}
		}
	}
}

void executeUpgrade(char upCode, Palette* palette, BallDArray* balls) {
	switch (upCode){
	case 0: // Penetrating ball
		for (unsigned int i = 0; i < balls->size; i++) *(double*)balls->arr[i]->userParam = 5.0;
		break;
	case 1: // Wider palette
		palette->w = min(palette->w + 0.5 / 16, 8.0 / 16);
		break;
	case 2: // Thiner palette
		palette->w = max(palette->w - 0.5 / 16, 2.0 / 16);
		break;
	case 3: // Faster balls
		for (unsigned int i = 0; i < balls->size; i++) {
			balls->arr[i]->speed[0] += 0.05;
			balls->arr[i]->speed[1] += 0.05;
		}
		break;
	case 4: // Slower balls
		for (unsigned int i = 0; i < balls->size; i++) {
			balls->arr[i]->speed[0] -= 0.05;
			balls->arr[i]->speed[1] -= 0.05;
		}
		break;
	case 5: // Duplicate balls
		{
			unsigned int size = balls->size;
			for (unsigned int i = 0; i < size; i++) {
				Ball* ball = balls->arr[i];
				if (ball->speed[0] > ball->speed[1]) {
					appendBallDArray(balls, createBall(ball->x, ball->y, ball->speed[0] * -1, ball->speed[1], *(double*)ball->userParam));
				}
				else {
					appendBallDArray(balls, createBall(ball->x, ball->y, ball->speed[0], ball->speed[1] * -1, *(double*)ball->userParam));
				}
			}
		}
		break;
	}
}