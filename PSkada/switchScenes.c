#include "switchScenes.h"

#include "GLOBALVARS.h"
#include "menu.h"
#include "game.h"
#include "help.h"
#include "highscores.h"

void switchScenes(int newSceneNumber) {
	scene_del(); // Deaktywacja aktualnej sceny
	sceneNumber = newSceneNumber; // Zmiana sceny
	scene_init(); // Aktywacja
}

void scene_init() {
	switch (sceneNumber) {
	case 0:
		menu_init();
		break;
	case 1:
		game_init();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		help_init();
		break;
	case 5:
		highscores_init();
		break;
	default:
		break;
	}
}

void scene_del() {
	switch (sceneNumber){
	case 0:
		menu_del();
		break;
	case 1:
		game_del();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		help_del();
		break;
	case 5:
		highscores_del();
		break;
	default:
		break;
	}
}