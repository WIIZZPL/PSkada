#pragma once

#include "circle.h"
#include <stdio.h>
  
typedef Circle Upgrade;

Upgrade* createUpgrade(float x, float y);

int updateUpgrade(Upgrade* thisUpgrade, double dt); // Retruns 1 if it needs deletion
void renderUpgrade(Upgrade* thisUpgrade, double lag);

void destroyUpgrade(Upgrade** thisUpgrade);