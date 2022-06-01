#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "GLOBALVARS.h"
#include "switchScenes.h"
#include "Button.h"

int menu_init();


void menu_processImput(ALLEGRO_EVENT* event);
void menu_update(double t, double dt);
void menu_render(ALLEGRO_DISPLAY* display);
void endgame_render(ALLEGRO_DISPLAY* display);

void menu_del();