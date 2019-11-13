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


/*
    Parte principal do programa, responsável por iniciar e 
    chamar as funções auxiliares.
*/
int main(){
    char matrix[ROWS][COLUMNS];
    Bloco tijolo;
    int keypressed=0;

    //apagar o cursor da tela
   // ShowConsoleCursor(0);
    //system("cls");

    //posicao inicial do personagem e sua forma
    initBar(&tijolo);

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
   
        drawBar(matrix, tijolo, PIXEL);
            
        //mostro a matriz na tela
        printMatrix(matrix);
          //posicionar o @ no meio da tela
        if (!collisionBar(matrix, tijolo, UNCHECK_SIDE, NONE)){
            drawBar(matrix, tijolo, EMPY);
            tijolo.i++;
        //faça posição anterior do @ ser apagada

       // if((tijolo.i + tijolo.height/2) < (ROWS-1)){
        //    drawBar(matrix, tijolo, EMPY);

            //faça posição anterior do @ ser apagada
           // if(tijolo.i < (ROWS-1)) tijolo.i++;

        }else{
            initBar(&tijolo);
        }
    
        //faço a posição da @ ir para a baixo
        //if(tijolo.i < (ROWS-1)) tijolo.i++;

        //lendo teclas
        keypressed = 0;
        if(kbhit())keypressed = getch();
        if(keypressed==ARROWS) keypressed  = getch();

        switch(keypressed){
            //se move para esquerda
            case LEFT: 
            case TECLA_a:
            case TECLA_A:
                if(!collisionBar(matrix, tijolo, CHECK_SIDE, LEFT))
                        tijolo.j--;//esquerda
            break;
            //se move para direita
            case RIGHT:
            case TECLA_d: 
            case TECLA_D:
                if(!collisionBar(matrix, tijolo, CHECK_SIDE, RIGHT))
                        tijolo.j++;//direita
            break;
            //muda a direcao 
            case TECLA_ESPACO:
                rotate(&tijolo);
            break;
        }

    }

    system("pause");

    return 0;
}