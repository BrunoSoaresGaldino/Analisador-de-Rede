

#ifndef STATISTICS_H
#define STATISTIC_H

#include "network.h"
#include "defs.h"


void Visit(Network *network,int *matrix,bool *visited_nodes,int node,int last_node,int connected_component);

int NumberOfOffLineNodes(Network *network);




#endif