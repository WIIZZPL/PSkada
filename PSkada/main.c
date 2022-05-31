#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>


#include "GLOBALVARS.h"
#include "processImput.h"
#include "update.h"
#include "render.h"
#include "switchScenes.h"

int main(){
	

    //INITIALISE
	
	if (!al_init()) return;
	if (!al_init_image_addon()) return;
	if (!al_init_font_addon()) return;
	if (!al_init_ttf_addon()) return;
	if (!al_init_primitives_addon()) return;


	
	//Display & window
	displayWidth = 1280;
	displayHeight = 720;
	displayX = 0;
	displayY = 0;
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* display = al_create_display(displayWidth, displayHeight);
	if (!display) return;

	//Imput event queue
	processImput_init(display);

	//GAME LOOP
	
	running = 1;
	sceneNumber = 0;
	scene_init();
	double time = 0;
	const double SPT = 1 / 120.0;

	double FPS[10];
	int FPSi = 0;
	double lastFrameTime = al_current_time(), deltaFrameTime = 0, accumulatedTime = 0;
	
	while (running){
		deltaFrameTime = al_current_time() - lastFrameTime;
		lastFrameTime += deltaFrameTime;
		accumulatedTime += deltaFrameTime;

		//PROCESS IMPUT

		processImput();

		while (accumulatedTime >= SPT){
			
			//UPDATE
			
			update(time, SPT);
			
			accumulatedTime -= SPT;
			time += SPT;
		}

		//RENDER
 
		render(display, accumulatedTime);
		
		//Licznik FPS

		FPS[FPSi] = 1 / deltaFrameTime;
		FPSi = (FPSi + 1) % 10;
		double MFPS = 0;
		for (int i = 0; i < 10; i++) MFPS += FPS[i] / 10;
		char title[32];
		snprintf(title, 32, "PSkada FPS:%4.2lf", MFPS);
		al_set_window_title(display, title);
	}

	//UNINITIALISE
	
	scene_del();

	processImput_del(display);

	al_destroy_display(display);

	return 0;
}