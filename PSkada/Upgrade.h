#pragma once

#include "circle.h"
#include <stdio.h>
  
typedef Circle Upgrade;

#define UPGRADE_RADIUS (1.0/128)

Upgrade* createUpgrade(float x, float y);

void moveUpgrade(Upgrade* thisUpgrade, double dt);
void renderUpgrade(Upgrade* thisUpgrade, double lag);

void destroyUpgrade(Upgrade** thisUpgrade);