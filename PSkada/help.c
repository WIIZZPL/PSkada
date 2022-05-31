# include "help.h"

Button* buttonBack;
ALLEGRO_BITMAP* background;
Rectangle* information;

int help_init() {

	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);

	buttonBack = createRectangle(6.0 / 16, 7.5 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskBack.png"));
	if (!buttonBack) return 0;

	information = createRectangle(4.0 / 16, 1.0 / 9, 8.0 / 16, 6.0 / 9, al_load_bitmap("information.png"));
	if (!information) return 0;
	return 1;
}	

void help_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		 if (pointCollisionButton(buttonBack, event->mouse.x, event->mouse.y)) switchScenes(0);
	}
}

void help_render(ALLEGRO_DISPLAY* display) {
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderRectangle(buttonBack);
	renderRectangle(information);
}

void help_update(double t, double dt) {
	return;
}

void help_del() {
	destroyRectangle(&buttonBack);
	destroyRectangle(&information);
	al_destroy_bitmap(background);

}