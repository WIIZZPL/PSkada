#include "menu.h"

Button* buttonStart;
Button* buttonHighscore;
Button* buttonHelp;
Button* buttonQuit;
ALLEGRO_BITMAP* background;
ALLEGRO_SAMPLE* menuTheme;
float volume=0.4; //music volume
int menu_init() {
	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);
	//Music
	if (!al_install_audio()) return;
	if (!al_init_acodec_addon()) return;
	al_reserve_samples(1);
	menuTheme = al_load_sample("menu_slower.wav");
	al_play_sample(menuTheme, 0.4, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

	buttonStart = createRectangle(5.0 / 16, 4.0 / 9, 6.0 / 16, 1.0 / 9, al_load_bitmap("przyciskStart.png"));
	if (!buttonStart) return 0;

	buttonHighscore = createRectangle(6.0 / 16, 5.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskHighscores.png"));
	if (!buttonHighscore) return 0;

	buttonHelp = createRectangle(6.0 / 16, 6.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskHelp.png"));
	if (!buttonHelp) return 0;

	buttonQuit = createRectangle(6.0 / 16, 7.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskQuit.png"));
	if (!buttonQuit) return 0;

	return 1;
}

void menu_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		if (pointCollisionButton(buttonStart, event->mouse.x, event->mouse.y))
		{
			al_destroy_sample(menuTheme); //destroying music before start a game
			switchScenes(1);
		}
		else if (pointCollisionButton(buttonHighscore, event->mouse.x, event->mouse.y)) switchScenes(5);
		else if (pointCollisionButton(buttonHelp, event->mouse.x, event->mouse.y)) switchScenes(4);
		else if (pointCollisionButton(buttonQuit, event->mouse.x, event->mouse.y)) running = 0;
	}
}

void menu_update(double t, double dt) {
	return;
}

void menu_render(ALLEGRO_DISPLAY* display) {
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderRectangle(buttonStart);
	renderRectangle(buttonHighscore);
	renderRectangle(buttonHelp);
	renderRectangle(buttonQuit);
}

void menu_del() {
	destroyRectangle(&buttonStart);
	destroyRectangle(&buttonHighscore);
	destroyRectangle(&buttonHelp);
	destroyRectangle(&buttonQuit);
	al_destroy_bitmap(background);

}