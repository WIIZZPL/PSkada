#include "render.h"

#include "menu.h"
#include "game.h"
#include "help.h"
#include "highscores.h"

//Funkcja sluzy do wybrania funkcji renderowania danej sceny.
//Kazda owa funkcja potrzebuje jako parametr display oraz lag.

void render(ALLEGRO_DISPLAY* display, double lag) {
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	switch (sceneNumber){
	case 0: //Menu
		menu_render(display);
		break;
	case 1: //Gra
		game_render(display, lag);
		break;
	case 2: //Win game
		al_clear_to_color(al_map_rgb(0, 255, 255));
		break;
	case 3: //Loose game
		al_clear_to_color(al_map_rgb(255, 0, 0));
		break;
	case 4: //Help
		help_render(display);
		break;
	case 5: //Highscores
		highscores_render(display);
		break;
	default:
		al_clear_to_color(al_map_rgb(128, 128, 128));
		break;
	}

	al_flip_display();
}