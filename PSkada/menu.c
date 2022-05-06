#include "menu.h"

#include "switchScenes.h"

Rectangle* przyciskStart;
Rectangle* przyciskHighscore;
Rectangle* przyciskOpcje;
Rectangle* przyciskCredits;
Rectangle* przyciskQuit;

int menu_init() {
	przyciskStart = createRectangle(4.0 / 16, 4.0 / 9, 8.0 / 16, 1.0 / 9, al_load_bitmap("przyciskStart.png"));
	if (!przyciskStart) return 0;

	przyciskHighscore = createRectangle(4.0 / 16, 5.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskHighscores.png"));
	if (!przyciskHighscore) return 0;

	przyciskOpcje = createRectangle(8.0 / 16, 5.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskOptions.png"));
	if (!przyciskOpcje) return 0;

	przyciskCredits = createRectangle(4.0 / 16, 6.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskCredits.png"));
	if (!przyciskCredits) return 0;

	przyciskQuit = createRectangle(8.0 / 16, 6.0 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskQuit.png"));
	if (!przyciskQuit) return 0;

	return 1;
}

void menu_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		if (pointCollisionRectangle(przyciskStart, event->mouse.x, event->mouse.y)) switchScenes(1);
		else if (pointCollisionRectangle(przyciskHighscore, event->mouse.x, event->mouse.y)) switchScenes(3);
		else if (pointCollisionRectangle(przyciskOpcje, event->mouse.x, event->mouse.y)) switchScenes(4);
		else if (pointCollisionRectangle(przyciskCredits, event->mouse.x, event->mouse.y)) switchScenes(5);
		else if (pointCollisionRectangle(przyciskQuit, event->mouse.x, event->mouse.y)) running = 0;
	}
}

void menu_update(double t, double dt) {
	return;
}

void menu_render(ALLEGRO_DISPLAY* display) {
	al_draw_filled_rectangle(displayX, displayY, displayWidth + displayX, displayHeight + displayY, al_map_rgb(42, 157, 143));
	
	renderRectangle(przyciskStart);
	
	renderRectangle(przyciskHighscore);
	
	renderRectangle(przyciskOpcje);
	
	renderRectangle(przyciskCredits);
	
	renderRectangle(przyciskQuit);
}

void menu_del() {
	destroyRectangle(przyciskStart);
	destroyRectangle(przyciskHighscore);
	destroyRectangle(przyciskOpcje);
	destroyRectangle(przyciskCredits);
	destroyRectangle(przyciskQuit);
}