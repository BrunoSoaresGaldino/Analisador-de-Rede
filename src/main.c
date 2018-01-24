#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <math.h>
#include <locale.h>
#include <time.h>

#include "../include/network_analyzer.h"


int main(int argc ,char** argv)
{
    
    srand( (unsigned)time(NULL) );
    

    
    bool exit_program = false;


    Network *net = CreateNetwork( );
    Network *copy = NULL;

    int number_of_nodes = 0 ,number_of_arcs = 0;
   
    ToDo to_do;
    
    
    ParseArgs(argc,argv, &to_do );

    json_t *root = LoadJsonFile(to_do.network_file);
    
    CreateNodes(net,root);
    CreateArcs(net,root);
    
    json_decref(root);
    
//*********************************************************    
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    
    set_color_depth( 32 );
    
    if ( set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_WIDTH,SCREEN_HEIGHT,0,0) )
    {
        fputs("Configuracao de video nao suportada",stderr);
        
        DestroyNetwork( net );
        DestroyNetwork( copy );
        
        exit(EXIT_FAILURE);
    }
    
    set_window_title("Redes");
    
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
    
    BITMAP *buffer_hold = create_bitmap(SCREEN_W,SCREEN_H);
    
    BITMAP *arrow = load_bitmap("../images/arrow.bmp",NULL);
    
    if ( !arrow )
    {
        fputs("Nao foi possivel carregar o ponteiro do mouse",stderr);
        exit(EXIT_FAILURE);
    }
    
//********************************************************
    
   
   
    
    
    if( to_do.make_ensemble )
    {
    
        MakeEnsemble( &net, to_do.ensemble_from, to_do.ensemble_to,to_do.samples,to_do.output_file);
       
    }
    
    
    while( !exit_program )//loop de eventos
    {
     
       
        
        exit_program = UserAction(&net,&copy,buffer_hold);
        
        RemoveNodeOnClick( net , mouse_b , mouse_x , mouse_y );
        
        if( ( number_of_arcs != net->number_of_arcs ) || ( number_of_nodes != net->number_of_nodes ) )//só executa caso haja alguma variação na rede
        {
            
            number_of_arcs = net->number_of_arcs;
            
            number_of_nodes = net->number_of_nodes;
        
            VisitNodes( net );
        
            DrawNetwork( buffer_hold , net );
        
            DrawStats( buffer_hold, net );
            
           
        
        }
    
        draw_sprite(buffer,buffer_hold,0,0);
        
        if( key[KEY_F1])
        {
            key[KEY_F1] = 0;
            
            Help(); 
        }
        
        textprintf_ex(buffer,font,1,132,RED,-1,"Copia da rede? %c", copy ? 'S':'N');
        
        ShowNodeInfoMouseOn(net,mouse_x,mouse_y,buffer);
        
        draw_sprite(buffer,arrow,mouse_x,mouse_y);
        
        draw_sprite(screen,buffer,0,0);
        
        clear_to_color( buffer , WHITE );
       
        rest(1);
        
    }
    
   
    DestroyNetwork(net);    
    DestroyNetwork(copy);
    
    return EXIT_SUCCESS;
}
END_OF_MAIN()