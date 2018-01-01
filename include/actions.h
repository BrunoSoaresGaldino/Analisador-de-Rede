
#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>
#include <math.h>
#include <allegro.h>
#include <time.h>

#include "defs.h"
#include "network.h"
#include "statistics.h"
#include "io.h"
#include "TAD.h"

void RemoveNodeRandomly(Network *network);
void RemoveArcRandomly(Network *network);
void RemoveN_NodesRandomly(Network * network,float n);
void RemoveN_ArcsRandomly(Network * network,float n);
void VisitNodes(Network *network);
void SaveSats(Network *network,const char *file_name,int percent);
void MakeEnsemble(Network **network,int ensemble_from, int ensemble_to, int samples, const char *out_file );
void RemoveNodeOnClick(Network *network, int mouse_state,float mouse_x, float mouse_y );
void ShowNodeInfoMouseOn( Network * network,float mouse_x,float mouse_y,BITMAP *buffer);
bool UserAction( Network **network, Network **copy,BITMAP *buffer);
#endif