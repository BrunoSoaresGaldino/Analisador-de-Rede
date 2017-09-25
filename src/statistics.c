

#include "../include/statistics.h"

void Visit(Network* network, int* matrix, bool* visited_nodes, int node, int last_node, const char* connected_component)
{
    
    
    bool alone = true;// considero que o no esteja desconectado
    int i;
    
    if(visited_nodes[node])
        return;// caso ja tenha sido visitado, retorna
    
    visited_nodes[node] = true;// seta como visitado
    
    // seta a componente conetada
    strcpy(network->nodes[node]->connected_to,connected_component);
    network->nodes[node]->on_line = true;
    
    for(i = 0 ; i < network->number_of_nodes; i++ )// varre a linha correspondente
    {                                                //ao no na matriz.
        
        if( i == last_node)
            continue;// nao visita o no de onde veio
        
        if( *(matrix + (node*network->number_of_nodes)+ i) == 1)
        {
            alone = false;
            // visita os visinhos
            Visit(network,matrix,visited_nodes,i,node,connected_component);
        }
        
    }
    
    //if(alone && (last_node == node)) strcpy(network->nodes[node]->connected_to,"");
    
}



int NumberOfConnectedComponents(Network* network)
{
    if( !network->number_of_nodes )
        return 0;
    
    register int i,j,ccp = 0;
    // ccp eh um apontador para o topo do vetor de componentes

    bool add_component;
    
    //matriz de strings, que contera as componentes conectadas
    char connected_components[network->number_of_nodes][MAX_NAME_SIZE];
    
    
    // limpar a regiao de memoria em que ficarao as componentes
    memset( connected_components , 0 , network->number_of_nodes * MAX_NAME_SIZE);
    
    for(i = 0; i < network->number_of_nodes; i++)
    {
        add_component = true;
        
        for(j = 0; j < ccp ; j++)
            if( !strcmp( network->nodes[i]->connected_to , connected_components[j] ) )
                add_component = false;
            
        if(add_component)
        {
           
           strcpy(connected_components[ccp],network->nodes[i]->connected_to);
           ccp++;
        }
    }

    return ccp;
}



int LargestConnectedComponentSize(Network* network)
{
    if(!network->number_of_nodes)
        return 0;
    
    register int i,j,ccp,lcs;
    // ccp eh um apontador para o vetor de componentes
    // lcs ira armazenar o tamanho da maior componente
    
    bool add_component;
    
    char connected_components[network->number_of_nodes][MAX_NAME_SIZE];
    int connected_components_count[network->number_of_nodes];
    
    memset( connected_components,0,network->number_of_nodes * MAX_NAME_SIZE );
    
    memset( connected_components_count,0, network->number_of_nodes * sizeof (int) );
    
    
    ccp = 0;
    lcs=0;
    
    for(i = 0; i < network->number_of_nodes; i++)
    {
        add_component = true;
        
        for(j = 0; j < ccp ; j++)
        {
            if( !strcmp( network->nodes[i]->connected_to,connected_components[j]))
            {
                connected_components_count[j]++;
                add_component = false;
            }
                
        }
        if(add_component)
        {
            strcpy(connected_components[ccp],network->nodes[i]->connected_to);
            connected_components_count[ccp]++;
            ccp++;
        }
    }
    
    lcs = connected_components_count[0];
    
    for(i = 1; i < ccp; i++)
        if( connected_components_count[i] > lcs)
                lcs = connected_components_count[i];
            
    return lcs;    
    
    
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