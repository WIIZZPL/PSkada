# include "highscores.h"

Button* buttonBack;
ALLEGRO_BITMAP* background;
Rectangle* scoresBoard;

char highscoresText[5][17];

int highscores_init() {

	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);

	buttonBack = createRectangle(6.0 / 16, 7.5 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskBack.png"));
	if (!buttonBack) return 0;

	scoresBoard = createRectangle(4.0 / 16, 1.0 / 9, 8.0 / 16, 6.0 / 9, al_load_bitmap("highscores_board.png"));
	if (!scoresBoard) return 0;

	FILE* plik;
	unsigned long long highscores[5];
	for (int i = 0; i < 5; i++) highscores[i] = 0LL;
	if (!fopen_s(&plik, "Scores.bin", "rb")) {
		fread(highscores, sizeof(unsigned long long), 5, plik);
		fclose(plik);
	}
	for (int i = 0; i < 5; i++) {
		snprintf(highscoresText[i], 17, "%llu", highscores[i]);
	}

	return 1;
}

void highscores_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		if (pointCollisionButton(buttonBack, event->mouse.x, event->mouse.y)) switchScenes(0);
	}
}

void highscores_render(ALLEGRO_DISPLAY* display) {
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderButton(buttonBack);
	renderRectangle(scoresBoard);
	
	for (int i = 0; i < 5; i++) {
		int fontSize = 1.0/9 * displayHeight;
		int textX = displayX+displayWidth/2;
		int textY = displayY+displayHeight*(1.5/9 + 1.0/9*i);
		ALLEGRO_FONT* font = al_load_ttf_font("bahnschrift.ttf", fontSize, 0);

		al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_CENTRE, highscoresText[i]);

		al_destroy_font(font);
	}
}

void highscores_update(double t, double dt) {
	return;
}

void highscores_del() {
	destroyRectangle(&buttonBack);
	destroyRectangle(&scoresBoard);
	al_destroy_bitmap(background);
}