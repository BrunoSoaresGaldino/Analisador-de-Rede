
#ifndef DRAW_H
#define DRAW_H


#include <allegro.h>
#include <stdlib.h>

#include "defs.h"
#include "statistics.h"


void DrawNetwork(BITMAP *buffer,Network *network);
void DrawStats(BITMAP *buffer,Network * network);



#endif