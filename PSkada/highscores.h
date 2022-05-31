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

int highscores_init();

void highscores_processImput(ALLEGRO_EVENT* event);
void highscores_update(double t, double dt);
void highscores_render(ALLEGRO_DISPLAY* display);

void highscores_del();
