/*
    Jogo interativo Tetris implementado em linguagem C para uso 
    no console (terminal de comandos)

    Autor: William Yamada
    Data: 28/08/2019

*/

#include "tetris.h"

/*
    Inicializa a matriz principal com 'espaços vazios'
*/
void init(char matrix[ROWS][COLUMNS]){
    int i,j;

    for(i=0; i<ROWS; i++){
        for(j=0; j<COLUMNS; j++){
            matrix[i][j] = ' ';
        }
    }
}

/*
    Mostra o conteúdo da matriz principal na tela 
    do computador.
*/
void printMatrix(char matrix[ROWS][COLUMNS]){
    int i,j;

    printf("\t\t\t\t\t");
    //Linha de cima
    for(j=0; j<COLUMNS+2; j++){
        printf("*");
    }
    printf("\n");

    //Matriz do jogo
    for(i=0; i<ROWS; i++){        
        printf("\t\t\t\t\t*");
        for(j=0; j<COLUMNS; j++){
            printf("%c", matrix[i][j]);
        }
        printf("*\n");
    }

    printf("\t\t\t\t\t");
    //Linha de baixo
    for(j=0; j<COLUMNS+2; j++){
        printf("*");
    }
    printf("\n");

}

/*
    Desenha uma barra usando o simbolo do caractere ASCII passando por parâmetro.
*/

void drawBar(char matrix [ROWS][COLUMNS],Bloco barra, int simbolo){
    switch (barra.orientacao){
        case ORIENTACAO_DOWN:
        case ORIENTACAO_UP:
            if (barra.i-4>=0) matrix[barra.i-4][barra.j] = simbolo;
            if (barra.i-3>=0) matrix[barra.i-3][barra.j] = simbolo;
            if (barra.i-2>=0) matrix[barra.i-2][barra.j] = simbolo;
            if (barra.i-1>=0) matrix[barra.i-1][barra.j] = simbolo;
            matrix[barra.i][barra.j] = simbolo;
        break;
        case ORIENTACAO_RIGHT:
        case ORIENTACAO_LEFT:
            if (barra.j+1>=0) matrix[barra.i][barra.j+1] = simbolo;
            if (barra.j+2>=0) matrix[barra.i][barra.j+2] = simbolo;
            if (barra.j-2>=0) matrix[barra.i][barra.j-2] = simbolo;
            if (barra.j-1>=0) matrix[barra.i][barra.j-1] = simbolo;
            matrix[barra.i][barra.j] = simbolo;
        break;
    }
}