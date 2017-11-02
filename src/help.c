
#include "../include/help.h"

void Help( )
{
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
    
    if( !buffer )
    {
        allegro_message("Nao foi possivel criar buffer");
        return;
    }
    
    clear_to_color( buffer,WHITE);
    
    textprintf_ex(buffer,font,SCREEN_H/2,50,BLACK,-1,"Para criar uma copia da rede pressione a tecla C");
    textprintf_ex(buffer,font,SCREEN_H/2,65,BLACK,-1,"Para restaurar a rede, a partir da copia, pressione R");
    textprintf_ex(buffer,font,SCREEN_H/2,80,BLACK,-1,"Para deletar um arco aleatoreamente pressine  A");
    textprintf_ex(buffer,font,SCREEN_H/2,95,BLACK,-1,"Para deletar um no aleatoreamente pressine N");
    textprintf_ex(buffer,font,SCREEN_H/2,110,BLACK,-1,"Para salvar as informacoes da rede pressione S");
    textprintf_ex(buffer,font,SCREEN_H/2,125,BLACK,-1,"Para tirar um snapshot da tela pressine P");
    textprintf_ex(buffer,font,SCREEN_H/2,140,BLACK,-1,"Para deletar um no, clique sobre ele");
    
    while( !key[KEY_F1] && !key[KEY_ESC] )
    {
        
        draw_sprite( screen, buffer, 0,0 );
        
    }
    
    key[KEY_F1] = 0;
    key[KEY_ESC] = 0;
    
}