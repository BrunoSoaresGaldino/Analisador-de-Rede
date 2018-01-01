

#ifndef NETWORK_H
#define NETWORK_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jansson.h>

#include "defs.h"
#include "TAD.h"

Node *GetNodeAddress(Network* network,int node_index);
Arc *GetArcAddress(Network* network,int arc_index);

int GetNodeNumber(Network* network,Node* node);
int GetArcNumber(Network* network,Arc *arc);

Node *GetNodeAddressByName(Network *network,const char *node_name);
int GetNodeNumberByName(Network *network,const char *node_name);

void CreateNodes(Network *network,json_t *root);
void DestroyNode(Network *network,int node_index);


void CreateArcs(Network *network,json_t *root);
void DestroyArc(Network *network,int arc_index);


Network *CreateNetwork(void);
void DestroyNetwork(Network *network);
Network *CopyNetwork(Network *network);


Matrix *GetAdjacenceMatrix(Network *network);
void FreeAdjacenceMatrix(Matrix *matrix);

//******************************************************************************
#endif