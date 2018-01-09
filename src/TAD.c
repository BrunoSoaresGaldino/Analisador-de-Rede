
#include "../include/TAD.h"

Cell *NewCell( )
{
    Cell *cell = calloc( 1 , sizeof(Cell) );
    
    if( cell )
    {
        return cell;
    }        
    
    return NULL;
    
}

Matrix *NewMatrix( int lines , int columns )
{
    
    Matrix *matrix = calloc( 1 , sizeof( Matrix) );
   
    if( matrix )
    {
        
        matrix->cells = calloc( lines , sizeof( Cell ) );
    
        if( matrix->cells )
        {
            matrix->lines = lines;
    
            matrix->columns = columns;
            
            return matrix;
        }
        
        free( matrix );
       
    }
    
    return NULL;
    
}

bool MatrixSetValue( Matrix *matrix , int line , int column , int value )
{
    
    if( line < matrix->lines && column < matrix->columns && line > -1 && column > -1 )
    {
    
        Cell *cell = matrix->cells[line];
        Cell *aux = NULL;
    
        if( !cell )//empty line
        {
            if( ( matrix->cells[line] = NewCell( ) ) && value )
            {
                matrix->cells[line]->value = value;
                
                return true;
            }
       
            return false;
        }
    
        while( cell )
        {
            if( cell->column == column )//the cell already exists
            {
                if( value )
                {
                    cell->value = value;
                    
                    return true;
                    
                }
                
                else if( aux )
                {
                    aux->next = cell->next;
                }
                
                free( cell );
                
                return true;
                
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
                
                if( ( aux = NewCell( ) ) )
                {
                    
                    aux->next = cell->next;
                    
                    cell->next = aux;
                    
                    aux->value = value;
                    
                    aux->column = column;
                    
                    return true;
                    
                }
                
                return false;
            }
            
            aux = cell;
            
            cell = cell->next;
        }
        
        
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