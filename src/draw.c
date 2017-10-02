
#include "../include/draw.h"


void DrawNetwork( BITMAP *buffer, Network *network )
{
    
    int i;
    
    clear_to_color(buffer,WHITE);
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
    {
        
        if( network->nodes[i]->on_line )
        {
            
            circlefill( buffer, network->nodes[i]->pos_x * (SCREEN_WIDTH - DRAW_START) + DRAW_START, network->nodes[i]->pos_y * SCREEN_HEIGHT, NODE_RADIUS , GRAY );
            
        }
        else 
        {
            
            circlefill( buffer, network->nodes[i]->pos_x * (SCREEN_WIDTH - DRAW_START) + DRAW_START, network->nodes[i]->pos_y * SCREEN_HEIGHT , NODE_RADIUS , RED );
            
        }
        
        
    }
    
    for( i = 0 ; i < network->number_of_arcs ; i++ )
    {
        
        line(
            buffer,
            network->arcs[i]->node_a->pos_x * ( SCREEN_WIDTH - DRAW_START) + DRAW_START,
            network->arcs[i]->node_a->pos_y * SCREEN_HEIGHT ,
            network->arcs[i]->node_b->pos_x * ( SCREEN_WIDTH - DRAW_START ) + DRAW_START,
            network->arcs[i]->node_b->pos_y * SCREEN_HEIGHT ,
            GRAY
            );
        
    }
    
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
    {
        
        textprintf_ex(
                      buffer , font , 
                      network->nodes[i]->pos_x * ( SCREEN_W -DRAW_START) + DRAW_START,
                      network->nodes[i]->pos_y * SCREEN_HEIGHT ,
                      BLACK,-1,"%s",network->nodes[i]->connected_to);
    
    }
}



void DrawStats( BITMAP * buffer, Network *network)
{
    int components = NumberOfConnectedComponents(network);
    
    float inverse_components;
    
    if( components )
    {
        inverse_components = 1 / ( ( float)components );
    }
    
    else 
    {
        inverse_components = components;
    }
    
    textprintf_ex( buffer, font, 1,  2, BLACK, -1, "Nos: %d", network->number_of_nodes );
    textprintf_ex( buffer, font, 1, 12, BLACK, -1, "Arcos: %d", network->number_of_arcs );
    textprintf_ex( buffer, font, 1, 22, BLACK, -1, "Usinas: %d",network->number_of_generation_units);
    textprintf_ex( buffer, font, 1, 32, BLACK, -1, "Componentes: %d",components);
    textprintf_ex( buffer, font, 1, 42, BLACK, -1, "Componentes ^ -1: %.2f",inverse_components);
    textprintf_ex( buffer, font, 1, 52, BLACK, -1, "Maior Componente: %d",LargestConnectedComponentSize(network));
    textprintf_ex( buffer, font, 1, 62, BLACK, -1, "Nos desconectados: %d", NumberOfOffLineNodes(network) );
    
    line(buffer,DRAW_START,0,DRAW_START,SCREEN_HEIGHT,BLACK);
    
}