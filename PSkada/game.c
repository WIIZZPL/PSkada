#include "game.h"

char keyboardState[ALLEGRO_KEY_MAX];

Palette* palette;
Ball* ball;

BrickQTree* bricks;

void game_init() {
	palette = createPalette(6.0 / 16, 8.5 / 9, 4.0 / 16, 0.25 / 9, al_load_bitmap("palette.png"));
	ball = createBall(0.5, 0.5, 1.0/128, al_load_bitmap("ball.png"));
	
	bricks = createBrickQTree(0, 0, 1, 3.0/4);
	insertBrickQTree(bricks, createBrick(0.5 / 16, 0.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
	insertBrickQTree(bricks, createBrick(2.5 / 16, 0.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
	insertBrickQTree(bricks, createBrick(2.5 / 16, 1.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
	insertBrickQTree(bricks, createBrick(14.5 / 16, 5.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
	insertBrickQTree(bricks, createBrick(0.5 / 16, 1.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
	insertBrickQTree(bricks, createBrick(0.5 / 16, 2.5 / 9, 1.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png")));
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
	updatePalette(palette, dt, keyboardState);
	updateBall(&ball, palette, NULL, dt);
}

void game_render(ALLEGRO_DISPLAY* display, double lag) {
	al_draw_filled_rectangle(displayX, displayY, displayX + displayWidth, displayY + displayHeight, al_map_rgb(38, 0, 83));
	renderPalette(palette);
	renderBall(ball, lag);
	renderBrickQTree(bricks);
}

void game_del() {
	destroyPalette(&palette);
	destroyBall(&ball);
	destroyBrickQTree(&bricks);
}