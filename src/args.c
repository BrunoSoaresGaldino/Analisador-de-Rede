
#include "../include/args.h"

void ParseArgs(int argc, char *argv[],ToDo *to_do)
{
    int i;
    
    to_do->nodes_to_del = 0.0f;
    to_do->arcs_to_del = 0.0f;
    to_do->ensemble_from = 0;
    to_do->ensemble_to = 0;
    to_do->display = true;
    to_do->make_ensemble = false;
    strcpy(to_do->output_file,"../data/ensemble.csv");
    *to_do->network_file = '\0';
    to_do->samples = 1;
   
    if(argc < 2)
        return;
    
    for( i = 0 ; i < argc ; i++)
    {
        if( !strcmp(argv[i],DELETE))
        {
            if( !strcmp(argv[i+1],ARCS) )
            {
                i += 2;
                
                if( i < argc )
                    to_do->arcs_to_del = atof(argv[i]);    
            }
            
            else if( !strcmp(argv[i+1],NODES) )
            {
                i += 2;
                if( i < argc )
                    to_do->nodes_to_del = atof(argv[i]);
            }
        }
        else if ( !strcmp(argv[i],NOT_DISPLAY) )
        {
            
            to_do->display = false;
        }
        
        else if( !strcmp(argv[i],MAKE_ENSEMBLE))
        {
            
            to_do->make_ensemble = true;
            
            i++;
            if( i < argc )
                to_do->ensemble_from = atoi( argv[i] );
            
            i++;
            if( i < argc )
                to_do->ensemble_to = atoi( argv[i] );
        
        }
        
        else if ( !strcmp( argv[i],OUTPUT_FILE) )
        {
            i++;
            
            if( i < argc )
                strcpy(to_do->output_file, argv[i] );

            
        }
        else if( !strcmp( argv[i], NETWORK_FILE) )
        {
            
            i++;
            if( i < argc )
                strcpy(to_do->network_file,argv[i] );
            
        }
        else if( !strcmp(argv[i],SAMPLES) )
        {
            i++;
            
            if( i < argc )
            {
                to_do->samples = atoi(argv[i]);
            }
            
        }
        
        
    }
    
    
}