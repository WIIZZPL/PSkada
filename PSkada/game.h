#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#include "switchScenes.h"
#include "Palette.h"
#include "Ball.h"
#include "BallDArray.h"
#include "Upgrade.h"
#include "UpgradeDArray.h"
#include "Brick.h"
#include "BrickQTree.h"
#include "BrickDArray.h"

#define GAME_BOUNDBOX_X 0.0
#define GAME_BOUNDBOX_Y 0.0
#define GAME_BOUNDBOX_WIDTH 1.0
#define GAME_BOUNDBOX_HEIGHT 1.0

void game_init();

void game_processImput(ALLEGRO_EVENT* event);
void game_update(double t, double dt);
void game_render(ALLEGRO_DISPLAY* display, double lag);

void game_del();