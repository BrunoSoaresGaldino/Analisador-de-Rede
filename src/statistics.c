

#include "../include/statistics.h"

void Visit(Network* network, Matrix* matrix, bool* visited_nodes, int node, int last_node, int connected_component )
{   
    
    static int count = 0;
    
    int i = 0;
    
    if( visited_nodes[ node ] )
    {
        return;// caso ja tenha sido visitado, retorna
    }
    
    count++;
    
    visited_nodes[ node ] = true;// seta como visitado
    
    // seta a componente conetada
    
    network->nodes[node]->connected_component = connected_component;
    
    network->nodes[node]->on_line = true;
    
    for( i = 0 ; i < network->number_of_nodes; i++ )// varre a linha correspondente
    {                                                //ao no na matriz.
        
        if( i == last_node)
        {
            continue;// nao visita o no de onde veio
        }

        if( MatrixGetValue( matrix , node , i ) )
        {
            //visita os visinhos
            Visit(network,matrix,visited_nodes,i,node,connected_component);
           
        }
        
    }
    
    
    if( last_node != node)
    {
        return;
    }
    
    
    if( count > 1 )
    {
        network->number_of_connected_components++;
        
        if( count > network->greater_component_size )
        {
            network->greater_component_size = count;
        }
        
        if( network->number_of_connected_components )
        {   
            network->components_medium_size  = ( network->components_medium_size * (network->number_of_connected_components - 1 ) + count ) / network->number_of_connected_components;
        }
        
        
    }

    count = 0;
    
}

int NumberOfOffLineNodes(Network* network)
{
    int  i = 0;
    int off_line_nodes = 0;
    
    for( ; i < network->number_of_nodes; i++)
        if( !network->nodes[i]->on_line)
            off_line_nodes++;
    
    return off_line_nodes;
}