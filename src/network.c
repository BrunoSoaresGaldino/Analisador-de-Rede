

#include "../include/network.h"

//Obtem o enderco de um no, a partir do seu idice no array de nos da rede
Node *GetNodeAddress(Network *network,int node_index)
{
    if( ( node_index < 0 ) || ( node_index >= MAX_NODES ) || ( network->number_of_nodes == 0))// caso o indice seja invalido, retorna null
        return NULL;
    
    return network->nodes[node_index];
    
}


//Obtem o endereco de um arco, a partir de seu indice no array de arcos
Arc *GetArcAddress(Network *network,int arc_index)
{
    if( ( arc_index < 0 ) || ( arc_index >= MAX_ARCS ) || ( network->number_of_arcs == 0 ) )//caso o indice seja invalido, retorna null
        return NULL;

    return network->arcs[arc_index];

}


//Obtem o indice de um no vetor de nos da rede,a partir de seu endereco de memoria
int GetNodeNumber(Network* network,Node* node)
{
    
    if( !node || !network->number_of_nodes )//caso o ponteiro passado seja nulo, ou a rede nao tenha nenhum no, retorna -1
        return -1;
        
    int i = 0;
    
    for(i = 0 ; i < network->number_of_nodes ; i++)
        if( network->nodes[i] == node )
            return i;
            
    return -1;// caso nao encontrado
}



//Obtem o indice de um arco no vetor de arcos da rede, a partir de seu endereco de memoria
int GetArcNumber( Network* network , Arc *arc )
{
    
    
    if( !arc || !network->number_of_arcs )
        return -1;
        
    int i = 0;
    
    for(i= 0 ; i < network->number_of_arcs ; i++)
        if( network->arcs[i] == arc )
            return i;

    return -1;//caso nao encontrado
    
}


// otem o endereco de um no a partir do seu nome
Node *GetNodeAddressByName( Network *network , const char *node_name )
{
    
    int i;
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
        if( !strcmp( network->nodes[i]->name, node_name ) )
            return network->nodes[i];
    
    return NULL;
    
}

int GetNodeNumberByName(Network *network,const char *node_name)
{
    
    int i;
    
    for( i = 0 ; i < network->number_of_nodes ; i++ )
        if( !strcmp( network->nodes[i]->name, node_name ) )
            return i;
        
    return -1;
}

//Cria um no e ajusta seus atributos de acordo com os parametros recebidos
void CreateNodes( Network *network , json_t *root )
{
    Node            *node;// ponteiro para o no a ser criado
    json_t          *nodes;// ponteiro para o array json, contendo as informações do nós
    json_t          *object;//ponteiro para um elemento do array de nós
    json_t          *key;// ponteiro para os atributos do nó
    const char      *str;
    int             array_c = 0;// contador os objetos do array nodes
    int             i = network->number_of_nodes;
    
    
    nodes = json_object_get(root,"nodes");
    
    if( !json_is_array(nodes))
    {
        
        fputs("Era esperado um array de nos",stderr);
        json_decref(root);
        exit(EXIT_FAILURE);
    }
    
    
    while( array_c < json_array_size(nodes) )
    {
        
        if( i == MAX_NODES)// verificao do limite maximo de nos
            return;
        
        
        node =  calloc(1,sizeof(Node));//aloca memoria para o no 
        
        if(!node)
            return;// caso haja falha aborta. Possivel causa de falha: sem memoria no heap
        
        object = json_array_get(nodes,array_c);
        
        if(!object)
            return;
        
        
        key = json_object_get(object,"name");
        if(key)
        {
            
            str = json_string_value(key);
            
            strncpy(node->name,str,MAX_NAME_SIZE-1);
            
            
        }
        
        
        key = json_object_get(object,"pos_x");
        if(key)
        {
        
            node->pos_x = json_real_value(key);
            
        }
        
        
        key = json_object_get(object,"pos_y");
        if(key)
        {
        
            node->pos_y = json_real_value(key);
        }
            
        
        key = json_object_get(object,"node_type");
        if(key)
        {
            
            node->node_type = json_integer_value(key);
            
        }
            
        
        key = json_object_get(object,"power_in");
        if(key)
        {
            
            node->power_in = json_real_value(key);

        }
        
        key = json_object_get(object,"power_out");
        if(key)
        {
            
            node->power_out = json_real_value(key);

        }
        
        
        key = json_object_get(object,"max_operation_power");
        if(key)
        {
            
            node->max_operation_power = json_real_value(key);

        }
        
        
        key = json_object_get(object,"min_operation_power");
        if(key)
        {
            
            node->min_operation_power = json_real_value(key);

        }        
            
            
        if( node->node_type == GENERATION_UNIT)
            network->number_of_generation_units++;
            
        network->nodes[i] = node;
        
        network->number_of_nodes++;
        
        i++;
        
        array_c++;
        
    }
    

}



void DestroyNode(Network *network,int node_index)
{
    
    if ( !network->number_of_nodes )
        return;
    
    Node *node = GetNodeAddress(network,node_index);
        if(!node)
            return;
    
    int i = 0;
    
    Arc *arcs_to_destroy[MAX_ARCS];//array para armazenar os arcos a serem excluidos da rede
    int arcs_to_destroy_c = 0;//contador dos arcos a serem destruidos
    
    if( node->node_type == GENERATION_UNIT)
        network->number_of_generation_units--;
    
    for( i = 0 ; i < network->number_of_arcs ; i++ )// laco para saber quais arcos contem o no a ser destruido
        if( (network->arcs[i]->node_a == node) || (network->arcs[i]->node_b == node))
            arcs_to_destroy[arcs_to_destroy_c++] = network->arcs[i];

    
    for(i = 0 ; i < arcs_to_destroy_c; i++)// destruir os nos necessarios
        DestroyArc( network,GetArcNumber( network,arcs_to_destroy[i] ) );
        
    
    for(i = node_index ; i < network->number_of_nodes-1 ; i++ )
        network->nodes[i] = network->nodes[i+1];//deslocar todos uma casa a esquerda no array
    
    network->number_of_nodes--;
    
    free(node); // libera a memoria alocada para o no
    
}



// Cria arcos
void CreateArcs(Network *network,json_t *root)
{
    Arc        *arc;
    json_t     *arcs;
    json_t     *object;
    json_t     *key;
    const char *str;
    int        array_c = 0;
    int        i = network->number_of_arcs;
    
    
    arcs = json_object_get(root,"arcs");
    
    
    if( !json_is_array(arcs))
        return;
    
    
    while( array_c < json_array_size(arcs) )
    {
        
        if( network->number_of_arcs == MAX_ARCS )
            return;// verifica se o numero maximo de arcos ja foi atingido,
    
        arc = calloc(1,sizeof(Arc) );
        
        if( !arc )
            return;
        
        object = json_array_get( arcs , array_c );
        
        if( !object )
            return;
        
        
        key = json_object_get( object , "name_a" );
        if(key)
        {
            str = json_string_value( key );
            arc->node_a = GetNodeAddressByName( network , str );
        }
        
        
        key = json_object_get( object , "name_b" );
        if(key)
        {
            str = json_string_value( key );
            arc->node_b = GetNodeAddressByName( network , str );
        }
        
        
        key = json_object_get( object , "num_a" );
        if( key )
        {
            arc->node_a = GetNodeAddress( network , json_integer_value( key ) - 1 );
        }
        
        key = json_object_get(object,"num_b");
        if(key)
        {
            arc->node_b = GetNodeAddress( network,json_integer_value( key ) - 1 );
        }
        
        
        if( !arc->node_a || !arc->node_b )// caso algum dos arcos seja invalido, pula a sua criacao
        {
            free( arc );
        
            continue;
        }
        
        
        key = json_object_get(object,"transported_power");
        if(key)
        {
            
            arc->transported_power = json_real_value(key);

        }
        
        network->arcs[i] = arc;
        
        network->number_of_arcs++;
        
        i++;
        
        array_c++;
    }

}



void DestroyArc(Network *network,int arc_index)
{
    
    if( !network->number_of_arcs );
    
    Arc *arc = GetArcAddress(network,arc_index);
    
    if( !arc )
        return;
    
    int i = 0;
        
    for( i = arc_index; i < network->number_of_arcs - 1 ; i++) 
        network->arcs[i] = network->arcs[i+1];// reposisicionar todos os arcos
    
    network->number_of_arcs--;
    
    free(arc);
    
    
}



Network *CreateNetwork(void)
{
    Network *network = calloc(1,sizeof(Network));
    
    if(!network)
    {
        perror("Nao foi possivel criar a rede");
        exit(EXIT_FAILURE);
        
    }
 
    return network;
}



void DestroyNetwork(Network *network)
{
    
    if( !network )
        return;
    
    while( network->number_of_arcs > 0)
        DestroyArc( network,network->number_of_arcs - 1 );    
    
    while(network->number_of_nodes > 0)
        DestroyNode( network,network->number_of_nodes - 1 ); 
    
    free( network ); // libera a memoria ocupada pela rede
    
    
}



Network *CopyNetwork(Network *network)
{
    
    Network *copy = CreateNetwork();
    
    Node    *node;
    Arc     *arc;
    int     i = 0;
    int     node_a_index;
    int     node_b_index;

    
    for( i = 0 ; i < network->number_of_nodes ; i++)
    {
        
        node = calloc( 1 , sizeof(Node) );
        
        if( !node )
        {
            DestroyNetwork(copy);
            return NULL;
        }
        
        *node = *(network->nodes[i]);
            
        copy->nodes[i] = node;
        
        if( node->node_type == GENERATION_UNIT )
        {
            copy->number_of_generation_units++;
        }
        
        copy->number_of_nodes++;
        
    }
   
    for( i = 0 ; i < network->number_of_arcs ; i++ )
    {
        arc = calloc( 1 , sizeof(Arc) );
        
        if( !arc )
            
        {   DestroyNetwork(copy);
            return NULL;
        }
        node_a_index = GetNodeNumber( network, network->arcs[i]->node_a );
        
        node_b_index = GetNodeNumber( network, network->arcs[i]->node_b );
        
        arc->node_a = GetNodeAddress( copy,node_a_index);
        
        arc->node_b = GetNodeAddress( copy, node_b_index);
        
        arc->direction = network->arcs[i]->direction;
        
        arc->weight = network->arcs[i]->weight;
        
        arc->transported_power = network->arcs[i]->transported_power;
        
        copy->arcs[i] = arc;
        
        copy->number_of_arcs++;
        
    }
   
  
    return copy;
    
}

Matrix *GetAdjacenceMatrix(Network *network)
{
    
    
    Matrix *matrix = NewMatrix( network->number_of_nodes , network->number_of_nodes );
    
    int i;
    
    if( !matrix )
    {
        perror("Nao foi possivel alocar memoria para a matriz adjacencia");
        exit(EXIT_FAILURE);
    
    }
    
    // varre o array de arcos da rede e seta na matriz as ligcoes encontradas
    //entre nos
    
    for( i = 0 ; i < network->number_of_arcs; i++ )
    {
        MatrixSetValue( matrix , GetNodeNumber( network, network->arcs[i]->node_a ) , GetNodeNumber( network, network->arcs[i]->node_b) , 1 );
        MatrixSetValue( matrix , GetNodeNumber( network, network->arcs[i]->node_b ) , GetNodeNumber( network, network->arcs[i]->node_a) , 1 );
        
    }
    
    return matrix;

}

void FreeAdjacenceMatrix(Matrix *matrix)
{
    if( matrix )//caso seja passado um ponteiro valido, desaloca
    {
        DestroyMatrix( matrix );
    }
}