#include "endgame.h"

Button* buttonReturn;
ALLEGRO_BITMAP* background;
ALLEGRO_SAMPLE* menuTheme;
float volume;

int endgame_init() {
	background = al_load_bitmap("menu_background1.png");
	if (!background) exit(138);

	//Music
	volume = 0.4;
	al_reserve_samples(1);
	menuTheme = al_load_sample("menuTheme.mp3");
	if (menuTheme) al_play_sample(menuTheme, volume, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
	buttonReturn = createRectangle(6.0 / 16, 7.5 / 9, 4.0 / 16, 1.0 / 9, al_load_bitmap("przyciskBack.png"));
	if (!buttonReturn) return 0;

	return 1;
}

void endgame_processImput(ALLEGRO_EVENT* event) {
	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		 if (pointCollisionButton(buttonReturn, event->mouse.x, event->mouse.y)) switchScenes(0);
	}
}


void endgame_update(double t, double dt) {
	return;
}


//Render after game
void endgame_render(ALLEGRO_DISPLAY* display)
{
	al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), displayX, displayY, displayWidth, displayHeight, 0);
	renderRectangle(buttonReturn);
	int fontSize = 1.3 / 9 * displayHeight;
	int textX = displayX + displayWidth / 2;
	int textY = displayY + displayHeight / 3;
	char scoretext[32];
	snprintf(scoretext, 32, "Your Score %llu", thisScore);
	ALLEGRO_FONT* font = al_load_ttf_font("bahnschrift.ttf", fontSize, 0);
	if (thisScore > 0)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_CENTRE, "You win!!!");
		al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY + 100, ALLEGRO_ALIGN_CENTRE, scoretext);
	}
	else
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_CENTRE, "You loose!!!");
	}
	al_destroy_font(font);

}


void endgame_del() {
	destroyRectangle(&buttonReturn);
	al_destroy_bitmap(background);
	al_destroy_sample(menuTheme);

}