#include "game.h"

char keyboardState[ALLEGRO_KEY_MAX];

double gameTimer;

Palette* palette;
BallDArray* balls;
UpgradeDArray* upgrades;
BrickDArray* bricks;
ALLEGRO_BITMAP* background;
ALLEGRO_SAMPLE* gameTheme;

void handleColissions(Palette* palette, BallDArray* balls, UpgradeDArray* upgrades, BrickDArray* bricks);
int rectangleCircleColission(Rectangle* thisRectangle, Circle* thisCircle);
void brickQTreeBallColission(BrickQTree* bricksQTree, BrickDArray* bricks, Ball* thisBall, UpgradeDArray* upgrades);
void executeUpgrade(char upCode, Palette* palette, BallDArray* balls);

void game_init() {
	srand(time(NULL));
		
	background = al_load_bitmap("game_background.png");
	if (!background) exit(138);
	
	//Music
	al_reserve_samples(1);
	char sampleFileName[16];
	snprintf(sampleFileName, 16, "gameTheme%d.mp3", rand()%3);
	gameTheme = al_load_sample(sampleFileName);
	
	if(gameTheme) al_play_sample(gameTheme, 0.4, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

	gameTimer = al_get_time();
	
	palette = createPalette(6.0 / 16, 8.5 / 9, 4.0 / 16, 0.25 / 9);
	
	balls = createBallDArray();
	float ballStartX = (float)rand() / RAND_MAX * 4.0 / 16 + 6.0 / 16; // Pilka pojawia sie losowo na paletce
	appendBallDArray(balls, createBall(ballStartX, 8.5/9 - BALL_RADIUS, 0, 0.5, 0.0));

	upgrades = createUpgradeDArray();

	bricks = createBrickDArray();
	for (int i = 0; i < 16; i++) {
		for (int j = 2; j < 9; j++) {
			appendBrickDArray(bricks, createBrick(1.0/16*i, 0.5/9*j));
		}
	}
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
	gameTimer += dt;
	movePalette(palette, dt, keyboardState);
	moveBallDArray(balls, dt);
	moveUpgradeDArray(upgrades, dt);
	handleColissions(palette, balls, upgrades, bricks);
	if (!bricks->size) {
		//printf("Time: %lf\n", gameTimer);
		thisScore = llrint(1000*240/gameTimer);
		//printf("SCORE: %llu\n", thisScore);
		FILE* plik;
		unsigned long long highScores[5];
		for (int i = 0; i < 5; i++) highScores[i] = 0LL;
		if (!fopen_s(&plik, "Scores.bin", "rb+")) {
			fread(highScores, sizeof(unsigned long long), 5, plik);
			int i = 0;
			while (highScores[i] > thisScore && i < 5) i++;
			for (int j = 4; j > i; j--) highScores[j] = highScores[j - 1];
			highScores[i] = thisScore;
		}
		else {
			fopen_s(&plik, "Scores.bin", "wb");
			highScores[0] = thisScore;
		}
		//for (int i = 0; i < 5; i++) printf("%llu\n", highScores[i]);
		fflush(plik);
		fwrite(highScores, sizeof(unsigned long long), 5, plik);
		fclose(plik);
		
		switchScenes(2);
	} else if (!balls->size) switchScenes(0);
	
}

void game_render(ALLEGRO_DISPLAY* display, double lag) {
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderPalette(palette);
	renderBallDArray(balls, lag);
	renderBrickDArray(bricks);
	renderUpgradeDArray(upgrades, lag);
	//renderBrickQTree(bricks, GAME_BOUNDBOX_X, GAME_BOUNDBOX_Y, GAME_BOUNDBOX_WIDTH, GAME_BOUNDBOX_HEIGHT);
}

void game_del() {
	destroyPalette(&palette);
	destroyBallDArray(&balls);
	destroyUpgradeDArray(&upgrades);
	destroyBrickDArray(&bricks);
	al_destroy_sample(gameTheme);
	al_destroy_bitmap(background);
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
		ball->x = fmax(GAME_BOUNDBOX_X + ball->r, fmin(GAME_BOUNDBOX_X + GAME_BOUNDBOX_WIDTH - ball->r, ball->x));
		ball->y = fmax(GAME_BOUNDBOX_Y + ball->r, fmin(GAME_BOUNDBOX_Y + GAME_BOUNDBOX_HEIGHT - ball->r, ball->y));

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
		//printf("%lf Checking colissions in %p\n", al_get_time(), bricksQTree);
		for (int i = 0; i < bricksQTree->size; i++) {
			if (bricksQTree->bricks[i] >= bricks->arr+bricks->size) continue;
			Brick* brick = *bricksQTree->bricks[i];
			//printf("%lf Checking colission with %p\n", al_get_time(), brick);
			nx = max(brick->x, min(brick->x + brick->w, thisBall->x));
			ny = max(brick->y, min(brick->y + brick->h, thisBall->y));
			if (powf(fabsf(nx - thisBall->x), 2) + powf(fabsf(ny - thisBall->y), 2) <= powf(thisBall->r, 2)) {

				if (*(double*)thisBall->userParam <= 0.0) {
					if (nx == brick->x || nx == brick->x + brick->w) thisBall->speed[0] *= -1;
					if (ny == brick->y || ny == brick->y + brick->h) thisBall->speed[1] *= -1;
				}

				if((float)rand()/RAND_MAX <= 0.1) appendUpgradeDArray(upgrades, createUpgrade(brick->x + brick->w / 2, brick->y + brick->h / 2));

				//printf("%lf Removed %p\n", al_get_time(), brick);
				removeBrickDArray(bricks, bricksQTree->bricks[i]);
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