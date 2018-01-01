#include "../include/io.h"

size_t GetFileSize(FILE *file)
{
    size_t size = 0;
    
    fseek(file,0L,SEEK_END);
    
    size = ftell(file);
    
    fseek(file,0L,SEEK_SET);
    
    return size;
    
}



json_t *LoadJsonFile(const char *file_name)
{
    size_t       size = 0;
    char         *data;
    json_t       *root;
    json_error_t error;
    FILE         *file = fopen(file_name,"rb");
    
    if( !file )
    {
        perror("Nao foi possivel abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    size = GetFileSize(file);
    
    data = calloc(1,size+1);
    
    if( !data )
    {
        perror("Nao foi possivel alocar memoria para carregar o arquivo");
        exit(EXIT_FAILURE);
        
    }
    
    if( !( fread( data , 1 , size , file ) ) )
    {
        perror("Nao foi possivel ler os dados");
        exit(EXIT_FAILURE);
    }

    root = json_loads(data,0,&error);
    
    if( !root )
    {
        
        fprintf( stderr , "Erro na linha %d: %s", error.line , error.text );
        exit(EXIT_FAILURE);
    }
    
    fclose(file);
    
    return root;
    
}