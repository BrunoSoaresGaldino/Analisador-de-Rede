#ifndef TAD_C
#define TAD_C

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "defs.h"

Cell *NewCell( );
Matrix *NewMatrix( int lines , int colums );

bool MatrixSetValue( Matrix *matrix , int line , int column , int value );
int MatrixGetValue( Matrix *matrix , int line , int column );

void DestroyMatrix( Matrix *matrix);

#endif