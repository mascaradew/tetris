/*
    Jogo interativo Tetris implementado em linguagem C para uso 
    no console (terminal de comandos)

    para compilar: gcc main.c tetris.c display.c -o programa
                   ou  .\compile
    Para executar: start .\programa

    Autor: William Yamada
    Data: 28/08/2019

*/

#include "tetris.h"
#include "display.h"
#define DEBUG 1

/*
    Parte principal do programa, responsável por iniciar e 
    chamar as funções auxiliares.
*/
int main(){
    char matrix[ROWS][COLUMNS];
    Bloco tijolo;
    int keypressed=0;

    //posicao inicial do personagem e sua forma
    tijolo.i = 0;
    tijolo.j = COLUMNS/2;
    tijolo.tipo = TIPO_I;
    tijolo.orientacao = ORIENTACAO_LEFT;
    tijolo.width = 5;
    tijolo.height = 1;
    //inicializando matriz
    init(matrix);

    //apagar o cursor da tela
    ShowConsoleCursor(0);
    system("cls");

    //animação do jogo
    while(keypressed != ESC){        
        gotoxy(0,0);

        #if DEBUG == 1
            printf("Posicao = (%d,%d)\n\n", tijolo.i, tijolo.j);
            printf("Dimensao = (%d,%d)\n\n", tijolo.width, tijolo.height);

        #endif

        //posicionar o @ no meio da tela
        drawBar(matrix, tijolo, PIXEL);

        //mostro a matriz na tela
        printMatrix(matrix);

        //faça posição anterior do @ ser apagada
        drawBar(matrix, tijolo, EMPY);
    
        //faço a posição da @ ir para a baixo
        if(tijolo.i < (ROWS-1)) tijolo.i++;

        //lendo teclas
        keypressed = 0;
        if(kbhit())keypressed = getch();
        if(keypressed==ARROWS) keypressed  = getch();

        switch(keypressed){
            //se move para esquerda
            case LEFT: 
            case TECLA_a:
            case TECLA_A:
                if(tijolo.j - (tijolo.width/2) > 0) tijolo.j--;
            break;
            //se move para direita
            case RIGHT:
            case TECLA_d: 
            case TECLA_D:
                if(tijolo.j +  (tijolo.width/2) < (COLUMNS - 1)) tijolo.j++;
            break;
            //muda a direcao 
            case TECLA_ESPACO:
                if(tijolo.orientacao==ORIENTACAO_RIGHT)
                    tijolo.orientacao = ORIENTACAO_UP;
                else 
                    tijolo.orientacao++;
                
                //inverte as dimensoes do tijolo
                int aux = tijolo.width;
                tijolo.width = tijolo.height;
                tijolo.height = aux;

                //resolvendo bug dos cantos
                if(tijolo.j < (tijolo.width/2))
                    tijolo.j = tijolo.width/2;
                else if (tijolo.j > COLUMNS - (tijolo.width/2) - 1)
                    tijolo.j  = COLUMNS - (tijolo.width/2) -1;
        }

    }

    system("pause");

    return 0;
}