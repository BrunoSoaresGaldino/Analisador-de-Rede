

#ifndef NETWORK_H
#define NETWORK_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jansson.h>

#include "defs.h"

Node *GetNodeAddres(Network* network,int node_index);
Arc *GetArcAddres(Network* network,int arc_index);

int GetNodeNumber(Network* network,Node* node);
int GetArcNumber(Network* network,Arc *arc);

Node *GetNodeAddresFromName(Network *network,const char *node_name);
int GetNodeNumberFromName(Network *network,const char *node_name);

void CreateNode(Network *network,json_t *root);
void DestroyNode(Network *network,int node_index);


void CreateArc(Network *network,json_t *root);
void DestroyArc(Network *network,int arc_index);


Network *CreateNetwork(void);
void DestroyNetwork(Network *network);
Network *CopyNetwork(Network *network);


int *GetAdjacenceMatrix(Network *network);
void FreeAdjacenceMatrix(int *matrix);

//******************************************************************************
#endif