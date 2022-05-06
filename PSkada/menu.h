#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "GLOBALVARS.h"
#include "rectangle.h"

int menu_init();

void menu_processImput(ALLEGRO_EVENT* event);
void menu_update(double t, double dt);
void menu_render(ALLEGRO_DISPLAY* display);

void menu_del();