#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "GLOBALVARS.h"
#include "switchScenes.h"
#include "Button.h"
#include "menu.h"

int endgame_init();

void endgame_processImput(ALLEGRO_EVENT* event);
void endgame_update(double t, double dt);
void endgame_render(ALLEGRO_DISPLAY* display);

void endgame_del();
