#include "update.h"

#include "menu.h"
#include "game.h"
#include "endgame.h"
#include "help.h"
#include "highscores.h"

void update(double t, double dt) {

	switch (sceneNumber) {
	case 0: //Menu
		menu_update(t, dt);
		break;
	case 1: //Gra
		game_update(t, dt);
		break;
	case 2: endgame_update(t, dt); //Win game
		break;
	case 3: //Loose game
		break;
	case 4: //Help
		help_update(t, dt);
		break;
	case 5: //Highscores
		highscores_update(t, dt);
		break;
	default:
		break;
	}

}