#pragma once

#include <allegro5/allegro5.h>

void game_init();

void game_processImput(ALLEGRO_EVENT* event);
void game_update(double t, double dt);
void game_render(ALLEGRO_DISPLAY* display, double lag);

void game_del();