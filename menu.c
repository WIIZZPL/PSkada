#include "menu.h"

Button* buttonStart;
Button* buttonHighscore;
Button* buttonOptions;
Button* buttonCredits;
Button* buttonQuit;
ALLEGRO_BITMAP* background;

int menu_init() {
	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);

	buttonStart = createRectangle(4.0 / 16, 4.0 / 9, 8.0 / 16, 1.0 / 9, al_load_bitmap("przyciskStart.png"));
	if (!buttonStart) return 0;

	buttonHighscore = createRectangle(4.0 / 16, 5.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskHighscores.png"));
	if (!buttonHighscore) return 0;

	buttonOptions = createRectangle(8.0 / 16, 5.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskPomoc.png"));
	if (!buttonOptions) return 0;

	buttonCredits = createRectangle(4.0 / 16, 6.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskCredits.png"));
	if (!buttonCredits) return 0;

	buttonQuit = createRectangle(8.0 / 16, 6.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskQuit.png"));
	if (!buttonQuit) return 0;

	return 1;
}

void menu_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		if (pointCollisionButton(buttonStart, event->mouse.x, event->mouse.y)) switchScenes(1);
		else if (pointCollisionButton(buttonHighscore, event->mouse.x, event->mouse.y)) switchScenes(3);
		else if (pointCollisionButton(buttonOptions, event->mouse.x, event->mouse.y)) switchScenes(4);
		else if (pointCollisionButton(buttonCredits, event->mouse.x, event->mouse.y)) switchScenes(5);
		else if (pointCollisionButton(buttonQuit, event->mouse.x, event->mouse.y)) running = 0;
	}
}

void menu_update(double t, double dt) {
	return;
}

void menu_render(ALLEGRO_DISPLAY* display) {
	//al_draw_filled_rectangle(displayX, displayY, displayWidth + displayX, displayHeight + displayY, al_map_rgb(42, 157, 143));
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderRectangle(buttonStart);
	renderRectangle(buttonHighscore);
	renderRectangle(buttonOptions);
	renderRectangle(buttonCredits);
	renderRectangle(buttonQuit);
}

void menu_del() {
	destroyRectangle(&buttonStart);
	destroyRectangle(&buttonHighscore);
	destroyRectangle(&buttonOptions);
	destroyRectangle(&buttonCredits);
	destroyRectangle(&buttonQuit);
	al_destroy_bitmap(background);
}