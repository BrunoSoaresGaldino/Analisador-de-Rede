

#ifndef STATISTICS_H
#define STATISTIC_H

#include "network.h"
#include "defs.h"


void Visit(Network *network,int *matrix,bool *visited_nodes,int node,int last_node,const char *connected_component);

int NumberOfConnectedComponents(Network *network);

int LargestConnectedComponentSize(Network *network);

int NumberOfOffLineNodes(Network *network);




#endif