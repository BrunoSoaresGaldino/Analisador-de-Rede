
#include "../include/actions.h"


void RemoveNodeRandomly(Network *network)
{
    
    if( !network->number_of_nodes )
        return;
   
    
    int rand_number = rand() % ( network->number_of_nodes );
    
    DestroyNode( network , rand_number );
    
}



void RemoveArcRandomly(Network *network)
{
    
    if( !network->number_of_arcs )
        return;
    
    
    
    int rand_number = rand() % ( network->number_of_arcs );
    
    DestroyArc( network , rand_number );
    
}



void RemoveN_NodesRandomly( Network * network , float n )
{
    
    int nodes_to_remove = 0;
    int i = 0;
    int rand_number;
    
    
    if( n > 0.0f && n < 1.1f )// trata n como o percentual de nos a serem removidos
    {
        
        nodes_to_remove = network->number_of_nodes * n;
        
    }        
    
    else if ( n > 0.0f && fabsf(n - network->number_of_nodes) <= DIFERENCE )// trata n como sendo a quantide de nos a serem removidos
    {
        
        nodes_to_remove = n;
        
    }
    
   
    
    while( i < nodes_to_remove && network->number_of_nodes )
    {
        
        rand_number = rand() %  network->number_of_nodes;
        
        DestroyNode( network , rand_number );
        
        i++;
    }
    
    
}



void RemoveN_ArcsRandomly(Network * network,float n)
{
    
    int arcs_to_remove = 0;
    int i = 0;
    int rand_number;
   
    
    if( n > 0.0f && n < 1.0f )// trata n percentual de arcos a serem removidos
    {
        
        arcs_to_remove = network->number_of_arcs * n;
        
    }        
    
    else if ( n > 0.0f && fabsf(n - network->number_of_arcs) <= DIFERENCE )// trata n como sendo a quantide de arcos a serem removidos
    {
        
        arcs_to_remove = n;
        
    }
    
    
    while( i < arcs_to_remove && network->number_of_arcs )
    {
        
        rand_number = rand() %  network->number_of_arcs;
        
        DestroyArc(network,rand_number);
        
        i++;
    }
    
}


void VisitNodes( Network *network )
{
    

    bool visited_nodes[network->number_of_nodes];
    
    int *matrix = GetAdjacenceMatrix( network );
    
    int i;
    
    int g_u_c =  0;// generation_unit_counter
    
    network->number_of_connected_components = 0;
    
    network->greater_component_size = 0;
    
    network->components_medium_size = 0;
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
    {
        visited_nodes[i] = false;
        
        network->nodes[i]->connected_component = 0;
        
        network->nodes[i]->on_line = false;
    }
    
    for( i = 0; i < network->number_of_nodes  && g_u_c < network->number_of_generation_units ; i++ )
    {    

        if( network->nodes[i]->node_type == GENERATION_UNIT )
        {
            g_u_c++;
            
            Visit( network , matrix , visited_nodes, i , i , g_u_c );
            
        }           
        
    }
    
    
    FreeAdjacenceMatrix(matrix);
    
   
}


void SaveStats(Network *network, const char *file_name,int percent)
{
   
    
    FILE *file = fopen(file_name,"a");
    
    if( !file )
    {
        
        perror("Nao foi possivel abrir arquivo");
        return;
        
    }
    
    int components = network->number_of_connected_components;
    
    float inverse_components;
    
    if( components )
    {
        inverse_components = 1/ ( ( float)components );
    }
    else 
    {
        inverse_components = 0;
    }
    

    if ( GetFileSize(file) == 0)
    {
        fprintf(file,"%%,     Nos,    Arcos,  Usinas,  Componentes,  Componentes ^ -1,   Maior Componente,   Nos desconectados,\n");

    }
    
        fprintf(
                file,
                "%3d,   %4d,   %4d,     %3d,     %4d,           %0.2f,               %4d,                %4d,\n",
                percent,
                network->number_of_nodes,
                network->number_of_arcs,
                network->number_of_generation_units,
                components,
                inverse_components,
                network->greater_component_size,
                NumberOfOffLineNodes(network)
                );
    
    fclose(file);
    
}



void MakeEnsemble(Network **network,int ensemble_from, int ensemble_to,int samples, const char *out_file)
{
    float i;
    int j = 0;
    
    Network *copy = NULL;
    
    for( j = 0; j < samples; j++)
    {
        
        for( i = ensemble_from ; i <= ensemble_to ; i += 1 )
        {
        
            DestroyNetwork(copy);
            
            copy = CopyNetwork(*network);
            
            if( !copy )
            {
                allegro_message("Nao foi possivel fazer o Ensembly estatistico");
                return;
            }
            
            RemoveN_ArcsRandomly( copy , i/100 );
            
            VisitNodes( copy );
            
            SaveStats(copy,out_file,i);
            
        }
    
    }
}

void RemoveNodeOnClick( Network *network,int mouse_state,float mouse_x , float mouse_y )
{
    if( mouse_state == 1)
    {
       
        int i;
        
        for( i = 0 ; i < network->number_of_nodes ; i++ )
        {
            
            if ( 
                    
                    ( abs( mouse_x - ( network->nodes[i]->pos_x *(SCREEN_WIDTH - DRAW_START )+ DRAW_START ) ) <= NODE_RADIUS  ) 
                    && 
                    ( abs( mouse_y - ( network->nodes[i]->pos_y *(SCREEN_HEIGHT) ) ) ) <= NODE_RADIUS  
                
                ) 
                {
                    
                    DestroyNode( network , i );
                    return;
                }
        }
        
        
        
    }
    
}

void ShowNodeInfoMouseOn( Network * network,float mouse_x,float mouse_y, BITMAP *buffer )
{
    int i;
    
    for( i = 0 ; i < network->number_of_nodes; i++ )
    {
        
        if 
        ( 
            
            ( abs( mouse_x - ( network->nodes[i]->pos_x *(SCREEN_WIDTH - DRAW_START )+ DRAW_START ) ) <= NODE_RADIUS  ) 
            && 
            ( abs( mouse_y - ( network->nodes[i]->pos_y *(SCREEN_HEIGHT) ) ) ) <= NODE_RADIUS  
            
        ) 
        {
            rect(buffer,2,SCREEN_HEIGHT-200,DRAW_START-2,SCREEN_HEIGHT-2,RED);
            
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 198,BLACK,-1,"%s",network->nodes[i]->name);
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 188,BLACK,-1,"Tipo: %s", network->nodes[i]->node_type == GENERATION_UNIT ? "Geração": "Transmissão" );
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 178,BLACK,-1,"Potencia de saída: %.2f",network->nodes[i]->power_out );
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 168,BLACK,-1,"Potencia de entrada: %.2f", network->nodes[i]->power_in );
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 158,BLACK,-1,"Pot. máxima de operação: %.2f", network->nodes[i]->max_operation_power );
            textprintf_ex( buffer , font ,4,SCREEN_HEIGHT - 148,BLACK,-1,"Pot. mínima de operação: %.2f", network->nodes[i]->min_operation_power );
            
            break;
        }
        
        
        
    }
}

bool UserAction( Network **network , Network **copy , BITMAP *buffer )
{
    
    if(key[KEY_N])
    {
        RemoveNodeRandomly(*network);

        key[KEY_N] = 0;
        
        return false;
    }   
    
    if(key[KEY_A])
    {
       
        RemoveArcRandomly(*network);
        
        key[KEY_A] = 0;
        
        return false;
    }
    
    if( key[KEY_C] )
    {
        
        key[KEY_C] = 0;
        
        if( *copy )
        {
        
            DestroyNetwork( *copy ); 
            
            *copy = NULL;
            
            return false;
            
        }
        
        *copy = CopyNetwork( *network );
        
        if( !(*copy) )
        {
            allegro_message("Nao foi possivel copiar a rede");
            
        }
        
        return false;
        
    }
    
    if( key[KEY_R] )
    {
    
        if( *copy )
        {
            DestroyNetwork( *network );
        
            *network = CopyNetwork(*copy);
            
            if( !( *network ) )
            {
                allegro_message("Nao foi possivel restaurar a rede");
        
            }
        }
        
        key[KEY_R] = 0;
        
        return false;
        
    }
    
    if( key[KEY_P])
    {
        static int i = 1;
        
        char file_name[50];
        
        sprintf(file_name,"../images/screenshot%05d.bmp",i++);
        
        save_bitmap(file_name,buffer,NULL);
        
        key[KEY_P] = 0;
    }
    
    if( key[KEY_S] )
    {
        
        static int i = 1;
        
        char file_name[50];
        
        sprintf(file_name,"../data/stats%05d.csv",i++);
        
        SaveStats(*network,file_name,0.0);
        
        key[KEY_S] = 0;
        
    }
    
    if(key[KEY_ESC])
    {
       
        return true;
    }
    
    
    return false;
}
