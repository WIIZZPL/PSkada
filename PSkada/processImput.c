#include "processImput.h"

#include "menu.h"
#include "game.h"

ALLEGRO_EVENT_QUEUE* imputQueue;

void processImput_init(ALLEGRO_DISPLAY* display) {
	imputQueue = al_create_event_queue();
	
	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(imputQueue, al_get_display_event_source(display));
	al_register_event_source(imputQueue, al_get_keyboard_event_source());
	al_register_event_source(imputQueue, al_get_mouse_event_source());
}

void processImput() {
	
	ALLEGRO_EVENT event;
	while (al_get_next_event(imputQueue, &event)) {

		//Shared imput events
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = 0;
			continue;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
			al_acknowledge_resize(event.display.source);
			displayWidth = al_get_display_width(event.display.source);
			displayHeight = al_get_display_height(event.display.source);
			displayX = max(0, (displayWidth - displayHeight * aspectRatio) / 2);
			displayY = max(0, (displayHeight - displayWidth / aspectRatio) / 2);
			displayWidth -= 2 * displayX;
			displayHeight -= 2 * displayY;
		}
		

		switch (sceneNumber) {
		case 0: //menu
			menu_processImput(&event);
			break;
		case 1: //gra
			break;
		case 2: //end game
			break;
		case 3: //highscores
			break;
		case 4: //opcje
			break;
		case 5: //credits
			break;
		default:
			break;
		}
	}
}

void processImput_del(ALLEGRO_DISPLAY* display) {
	al_unregister_event_source(imputQueue, al_get_display_event_source(display));
	al_unregister_event_source(imputQueue, al_get_keyboard_event_source());
	al_unregister_event_source(imputQueue, al_get_mouse_event_source());

	al_uninstall_keyboard();
	al_uninstall_mouse();

	al_destroy_event_queue(imputQueue);
}