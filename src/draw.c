
#include "../include/draw.h"

int ComponentColor( int component_number )
{
    int c = component_number;
   
    return makecol( c*10, c ,  (c%50)*50 );
    
}

void DrawNetwork( BITMAP *buffer, Network *network )
{
    
    int i;
    
    clear_to_color( buffer , WHITE );
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
    {
        
        circlefill( buffer, network->nodes[i]->pos_x * (SCREEN_WIDTH - DRAW_START) + DRAW_START, 
        network->nodes[i]->pos_y * SCREEN_HEIGHT, NODE_RADIUS , ComponentColor( network->nodes[i]->connected_component) );
        
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
        
        textprintf_centre_ex(
                      buffer , font , 
                      network->nodes[i]->pos_x * ( SCREEN_W -DRAW_START) + DRAW_START,
                      network->nodes[i]->pos_y * SCREEN_HEIGHT - ( NODE_RADIUS/3) ,
                      network->nodes[i]->node_type == GENERATION_UNIT ? RED : WHITE,
                      -1,"%d",network->nodes[i]->connected_component );
                       
    }
    
}



void DrawStats( BITMAP * buffer, Network *network )
{
    int components = network->number_of_connected_components;
    
    float inverse_components;
    
    if( components )
    {
        inverse_components = 1 / ( ( float)components );
    }
    
    else 
    {
        inverse_components = components;
    }
    
    textprintf_ex( buffer, font, 1,  2, BLACK, -1, "Nós: %d", network->number_of_nodes );
    textprintf_ex( buffer, font, 1, 12, BLACK, -1, "Arcos: %d", network->number_of_arcs );
    textprintf_ex( buffer, font, 1, 22, BLACK, -1, "Usinas: %d",network->number_of_generation_units);
    textprintf_ex( buffer, font, 1, 32, BLACK, -1, "Componentes: %d",components);
    textprintf_ex( buffer, font, 1, 42, BLACK, -1, "Componentes ^ -1: %.2f",inverse_components);
    textprintf_ex( buffer, font, 1, 52, BLACK, -1, "Maior Componente: %d",network->greater_component_size);
    textprintf_ex( buffer, font, 1, 62, BLACK, -1, "Nós desconectados: %d", NumberOfOffLineNodes(network) );
    textprintf_ex( buffer, font, 1, 72, BLACK, -1, "Tam médio das compon: %.2f",network->components_medium_size );
    textprintf_ex( buffer, font, 1, 82, BLACK, -1, "Média de arcos por nó: %.2f",(float)network->number_of_arcs/(float)network->number_of_nodes );
    
    line(buffer,DRAW_START,0,DRAW_START,SCREEN_HEIGHT,BLACK);
    
}