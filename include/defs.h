
#ifndef DEFS_H
#define DEFS_H

#define     RED     makecol( 255, 0, 0 )
#define     BLACK   makecol( 0, 0 ,0 ) 
#define     WHITE   makecol( 255, 255, 255 )
#define     GRAY    makecol( 128, 128, 128 )


#define     NODE_RADIUS     4
#define     SCREEN_WIDTH    1280
#define     SCREEN_HEIGHT   680
#define     DRAW_START      ( 0.20 * SCREEN_WIDTH )

#define     MAX_NAME_SIZE           40
#define     MAX_FILE_NAME_SIZE      100
#define     MAX_COMMAND_LINE_ARGS   100


#define     MAX_NODES               1000
#define     MAX_ARCS                10000
#define     MAX_GENERATION_UNITS    25


#define     NODES           "nodes"
#define     ARCS            "arcs"
#define     MAKE_ENSEMBLE   "-mkensb"
#define     DELETE          "-d"
#define     NOT_DISPLAY     "-nd"
#define     OUTPUT_FILE     "-o"
#define     NETWORK_FILE    "-nf"
#define     SAMPLES         "-s"


#define     DIFERENCE   0.000001f

#define     DRAWN_COMPONENT_NUMBER 0

#include <stdbool.h>

typedef unsigned char NodeType;
enum {GENERATION_UNIT=1,TRANSMITION_UNIT};


typedef struct
{
    char name[MAX_NAME_SIZE];
    
    int connected_component;
    
    float pos_x;
    
    float pos_y;
    
    NodeType node_type;
    
    float power_in;// potencia de entrada
    
    float power_out;// potencia de saida total do no
    
    float min_operation_power;//
    
    float max_operation_power;
    
    bool on_line;
    
} Node;

typedef struct
{
    Node *node_a;
    
    Node *node_b;
    
    int direction;// -1 bi-direcional; 0 node_a -> node_b ; 1 node_b -> node_a
    
    float weight;
    
    float transported_power;// potencia que a ligacao transporta
    
} Arc;

typedef struct
{

    int number_of_nodes;
    
    int number_of_arcs;
    
    int number_of_generation_units;
    
    int number_of_connected_components;
    
    int greater_component_size;
    
    float components_medium_size;
    
    Node *nodes[MAX_NODES];
    
    Arc *arcs[MAX_ARCS];
    
} Network;

typedef struct
{
    float nodes_to_del;
    
    float arcs_to_del;
    
    int ensemble_from;
    
    int ensemble_to;
	
    bool  display;
    
    bool  make_ensemble;
    
    char output_file[MAX_FILE_NAME_SIZE];
    
    char network_file[MAX_FILE_NAME_SIZE];
    
    int samples;
    
}ToDo;

typedef struct Cell Cell;

struct Cell
{
    int value;
    
    int column;
    
    Cell *next;
    
};

typedef struct Matrix
{
    
    int lines;
    
    int columns;
    
    Cell **cells;
    
    
} Matrix;

#endif