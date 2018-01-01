
#include "../include/TAD.h"

Cell *NewCell( )
{
    Cell *cell = calloc( 1, sizeof(Cell) );
    
    if( !cell )
    {
        return NULL;
    }        
    
    return cell;
    
}

Matrix *NewMatrix( int lines , int columns , int elements, ... )
{
    Matrix *matrix = calloc( 1 , sizeof( Matrix));
    
    int i;
    int j;
    int z;
   
    va_list list;
   
    if( !matrix )
    {
        return NULL;
    }
    
    matrix->cells = calloc( lines , sizeof(Cell) );
    
    if( !matrix->cells )
    {
        free(matrix);
        
        return NULL;
        
    }
    
    matrix->lines = lines;
    
    matrix->columns = columns;
    
    va_start( list , elements );
    
    for( i = 0 , z = 0 ; i < lines && z < elements ; i++ )
    {
        for( j = 0 ; j < columns && z < elements ; j++ , z++ )
        {
            
            MatrixSetValue( matrix , i , j , va_arg( list , int ) );
            
        }    
        
        
    }
    
    va_end(list);
    
    return matrix;
    
}

bool MatrixSetValue( Matrix *matrix , int line , int column , int value )
{
    if( line > matrix->lines-1 || column > matrix->columns-1 || !value )
    {
        return false;
    }
    
    
    Cell *cell = matrix->cells[line];
    Cell *new_cell;
    
    if( !cell )//empty line
    {
       if( ( cell = matrix->cells[line] = NewCell( ) ) )
       {
            cell->value = value;
            return true;
       }
       
       return false;
    }
    
    while( cell )
    {
        if( cell->column == column )//the cell already exists
        {
            cell->value = value;
        }
        
        if( !cell->next )//the cell was the last
        {
            if( ( cell->next = NewCell( ) ) )
            {
                cell->next->value = value;
                
                cell->next->column = column; 
                
                return true;
                
            }
            
            return false;
        }
        
        if( cell->next->column > column )// the next cell have a greather column index
        {
            
            if( ( new_cell = NewCell( ) ) )
            {
                
                new_cell->next = cell->next;
                
                cell->next = new_cell;
                
                new_cell->value = value;
                
                new_cell->column = column;
                
                return true;
                
            }
            
            return false;
        }
        
        
        
        cell = cell->next;
    }
    
    return false;
    
}

int MatrixGetValue( Matrix *matrix , int line , int column )
{
    
    if( line < matrix->lines && column < matrix->columns && line > -1 && column > -1 )
    {
        Cell *cell = matrix->cells[line];
        
        while( cell )
        {
            if( cell->column == column )
            {
                return cell->value;
                
            }
            
            cell = cell->next;
        }
        
        
    }
    
    
    
    return 0;
    
}

void DestroyMatrix( Matrix *matrix )
{
    Cell *cell;
    Cell *aux;
    int i;
    
    for( i = 0 ; i < matrix->lines ; i++ )
    {
        cell = matrix->cells[i];
        
        while( cell )
        {
            aux = cell;
          
            cell = cell->next;
          
            free( aux );
        }
        
    }
    
    free( matrix->cells );
    
    free(matrix);
    
}