#include "game.h"

#include <allegro5/allegro_primitives.h>
#include "rectangle.h"
#include "circle.h"

char keyboardState[ALLEGRO_KEY_MAX];

Rectangle* palette;
double paletteSpeed = 0.3;
Circle* ball;

void game_init() {
	palette = createRectangle(6.0 / 16, 8.25 / 9, 4.0 / 16, 0.5 / 9, al_load_bitmap("przyciskStart.png"));
	float ballSpeed[2] = {0.3, 0.15};
	float ballAcceleration[2] = { 0, 0 };
	ball = createCircle(0.5, 0.5, 1.0/128, ballSpeed, ballAcceleration, al_map_rgb(255, 255, 255));
}

void game_processImput(ALLEGRO_EVENT* event) {
	//Rejestrowanie wcisniecia klawiszy; (bitowo) 11 - wcisniety, 10 - odcisniety nie zarejestrowany, 01 - wcisniety zarejestrowany.
	if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
		keyboardState[event->keyboard.keycode] = 3;
	}
	else if (event->type == ALLEGRO_EVENT_KEY_UP) {
		keyboardState[event->keyboard.keycode] = keyboardState[event->keyboard.keycode] ^ 1;
	}
}

void game_update(double t, double dt) {
	//MOVEMENT
	if (keyboardState[ALLEGRO_KEY_LEFT]) {
		palette->x -= paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_LEFT] = keyboardState[ALLEGRO_KEY_LEFT] ^ 2;
	}
	if (keyboardState[ALLEGRO_KEY_RIGHT]) {
		palette->x += paletteSpeed * dt;
		keyboardState[ALLEGRO_KEY_RIGHT] = keyboardState[ALLEGRO_KEY_RIGHT] ^ 2;
	}
	if (palette->x < 0) palette->x = 0;
	if (palette->x+palette->w > 1) palette->x = 1-palette->w;

	//Kolicja paletka - ulepszenia

	updateCircle(ball, dt);

	//Kolizja pilka paletka
	//Kolizja pilka bloczki

}

void game_render(ALLEGRO_DISPLAY* display, double lag) {
	al_draw_filled_rectangle(displayX, displayY, displayX + displayWidth, displayY + displayHeight, al_map_rgb(38, 0, 83));
	renderRectangle(palette);
	renderCircle(ball, lag);
}

void game_del() {
	destroyRectangle(palette);
}