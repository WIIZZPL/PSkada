#include "update.h"

#include "menu.h"
#include "game.h"

void update(double t, double dt) {

	switch (sceneNumber) {
	case 0: //Menu
		menu_update(t, dt);
		break;
	case 1: //Gra
		game_update(t, dt);
		break;
	case 2: //End game
		break;
	case 3: //Highscores
		break;
	case 4: //Opcje
		break;
	case 5: //Credits
		break;
	default:
		break;
	}

}