
#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>
#include <math.h>
#include <allegro.h>
#include <time.h>

#include "defs.h"
#include "network.h"


void RemoveNodeRandomly(Network *network);
void RemoveArcRandomly(Network *network);
void RemoveN_NodesRandomly(Network * network,float n);
void RemoveN_ArcsRandomly(Network * network,float n);
void VisitNodes(Network *network);
bool UserInput( Network **network, Network **copy);
void SaveSats(Network *network,const char *file_name,float percent);
void MakeEnsemble(Network **network,float ensemble_from, float ensemble_to, const char *out_file );

#endif