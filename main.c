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
    tijolo.orientacao = ORIENTACAO_UP;
    tijolo.width = 1;
    tijolo.height = 4;
    //inicializando matriz
    init(matrix);

    //apagar o cursor da tela
    ShowConsoleCursor(0);
    system("cls");

    //animação do jogo
    while(keypressed != ESC){        
        gotoxy(0,0);

        #if DEBUG == 1
            printf("PIXEL = (%d,%d)\n\n", tijolo.i, tijolo.j);
        #endif

        //posicionar o @ no meio da tela
        switch (tijolo.orientacao){
            case ORIENTACAO_UP:
                if (tijolo.i-3>=0) matrix[tijolo.i-3][tijolo.j] = PIXEL;
                if (tijolo.i-2>=0) matrix[tijolo.i-2][tijolo.j] = PIXEL;
                if (tijolo.i-1>=0) matrix[tijolo.i-1][tijolo.j] = PIXEL;
                matrix[tijolo.i][tijolo.j] = PIXEL;
            break;
            case ORIENTACAO_LEFT:
                if (tijolo.i-3>=0) matrix[tijolo.i][tijolo.j-3] = PIXEL;
                if (tijolo.i-2>=0) matrix[tijolo.i][tijolo.j-2] = PIXEL;
                if (tijolo.i-1>=0) matrix[tijolo.i][tijolo.j-1] = PIXEL;
                matrix[tijolo.i][tijolo.j] = PIXEL;
            break;
        }
        //mostro a matriz na tela
        printMatrix(matrix);

        //faça posição anterior do @ ser apagada
        switch (tijolo.orientacao){
            case ORIENTACAO_UP:
                if (tijolo.i-3>=0) matrix[tijolo.i-3][tijolo.j] = EMPY;
                if (tijolo.i-2>=0) matrix[tijolo.i-2][tijolo.j] = EMPY;
                if (tijolo.i-1>=0) matrix[tijolo.i-1][tijolo.j] = EMPY;
                matrix[tijolo.i][tijolo.j] = EMPY;
            break;
            case ORIENTACAO_LEFT:
                if (tijolo.i-3>=0) matrix[tijolo.i][tijolo.j-3] = EMPY;
                if (tijolo.i-2>=0) matrix[tijolo.i][tijolo.j-2] = EMPY;
                if (tijolo.i-1>=0) matrix[tijolo.i][tijolo.j-1] = EMPY;
                matrix[tijolo.i][tijolo.j] = EMPY;
            break;
        }
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
                if(tijolo.j > 0) tijolo.j--;
            break;
            //se move para direita
            case RIGHT:
            case TECLA_d: 
            case TECLA_D:
                if(tijolo.j < (COLUMNS - 1)) tijolo.j++;
            break;
        }

    }

    system("pause");

    return 0;
}