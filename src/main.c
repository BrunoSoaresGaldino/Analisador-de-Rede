#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <math.h>
#include <locale.h>

#include "../include/network_analyzer.h"


int main(int argc ,char** argv)
{
    
    setlocale(LC_ALL,NULL);
    
    int i;
    
    bool exit_program = false;
    
    ToDo to_do;
    
    ParseArgs(argc,argv,&to_do);
    
    Network *net = CreateNetwork();
    Network *copy = NULL;
    
    json_t *root = LoadJsonFile(to_do.network_file);
    
    CreateNode(net,root);
    CreateArc(net,root);
    
    json_decref(root);
    
    
    
//*********************************************************    
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    
    set_color_depth(24);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
    set_window_title("Redes");
    
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);

//********************************************************
    
   
   
    
    
    if( to_do.make_ensemble )
    {
    
        MakeEnsemble( &net, to_do.ensemble_from, to_do.ensemble_to,to_do.output_file);
       
    }
    
    
    while(!exit_program)//loop de eventos
    {
        
        
        
        VisitNodes(net);
        
        DrawNetwork(buffer,net);
        
        DrawStats(buffer,net);
        
        exit_program = UserInput(&net,&copy);
       
        for(i = 0 ; i < net->number_of_nodes;i++)
            textprintf_ex(buffer,font,net->nodes[i]->pos_x*SCREEN_W,net->nodes[i]->pos_y*SCREEN_H,BLACK,-1,"%s",net->nodes[i]->connected_to);
        
        show_mouse(buffer);
        draw_sprite(screen,buffer,0,0);  
        
    }
    
   
    DestroyNetwork(net);    
    
    return EXIT_SUCCESS;
}
END_OF_MAIN()