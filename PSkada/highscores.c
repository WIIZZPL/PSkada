# include "highscores.h"

Button* buttonBack;
ALLEGRO_BITMAP* background;
Rectangle* scoresBoard;

int highscores_init() {

	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);

	buttonBack = createRectangle(6.0 / 16, 7.5 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskBack.png"));
	if (!buttonBack) return 0;

	scoresBoard = createRectangle(4.0 / 16, 1.0 / 9, 8.0 / 16, 6.0 / 9, al_load_bitmap("highscores_board.png"));
	if (!scoresBoard) return 0;
	return 1;
}

void highscores_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		if (pointCollisionButton(buttonBack, event->mouse.x, event->mouse.y)) switchScenes(0);
	}
}

void highscores_render(ALLEGRO_DISPLAY* display) {
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderRectangle(buttonBack);
	renderRectangle(scoresBoard);
}

void highscores_update(double t, double dt) {
	return;
}

void highscores_del() {
	destroyRectangle(&buttonBack);
	destroyRectangle(&scoresBoard);
	al_destroy_bitmap(background);

}