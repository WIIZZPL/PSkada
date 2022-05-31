#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "GLOBALVARS.h"
#include "switchScenes.h"
#include "Button.h"
#include "rectangle.h"

int help_init();

void help_processImput(ALLEGRO_EVENT* event);
void help_update(double t, double dt);
void help_render(ALLEGRO_DISPLAY* display);

void help_del();
