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
    Desenha uma bloco usando o simbolo do caractere ASCII passando por parâmetro.
*/

void drawBar(char matrix [ROWS][COLUMNS],Bloco bloco, int simbolo){
    switch (bloco.orientacao){
        case ORIENTACAO_DOWN:
        case ORIENTACAO_UP:
            if (bloco.i-4>=0) matrix[bloco.i-4][bloco.j] = simbolo;
            if (bloco.i-3>=0) matrix[bloco.i-3][bloco.j] = simbolo;
            if (bloco.i-2>=0) matrix[bloco.i-2][bloco.j] = simbolo;
            if (bloco.i-1>=0) matrix[bloco.i-1][bloco.j] = simbolo;
            matrix[bloco.i][bloco.j] = simbolo;
        break;
        case ORIENTACAO_RIGHT:
        case ORIENTACAO_LEFT:
            if (bloco.j+1>=0) matrix[bloco.i][bloco.j+1] = simbolo;
            if (bloco.j+2>=0) matrix[bloco.i][bloco.j+2] = simbolo;
            if (bloco.j-2>=0) matrix[bloco.i][bloco.j-2] = simbolo;
            if (bloco.j-1>=0) matrix[bloco.i][bloco.j-1] = simbolo;
            matrix[bloco.i][bloco.j] = simbolo;
        break;
    }
}


/*
    Inicializar a peça do tipo bloco
*/
void initBar (Bloco *bloco){
    bloco->i = 0;
    bloco->j = COLUMNS/2;
    bloco->tipo = TIPO_I;
    bloco->orientacao = ORIENTACAO_LEFT;
    bloco->width = 5;
    bloco->height = 1;

//Verificação da posição inicial da bloco
    #if DEBUG == 1
        printf("posI %d posJ %d\n", bloco->i, bloco->j);
        system("pause");
    #endif
}

 /*
    Rotaciona Blocos do Jogo
 */

void rotate(Bloco *bloco){
    if(bloco->orientacao==ORIENTACAO_RIGHT)
        bloco->orientacao = ORIENTACAO_UP;
    else 
        bloco->orientacao++;
    
    //inverte as dimensoes do bloco
    int aux = bloco->width;
    bloco->width = bloco->height;
    bloco->height = aux;

    //resolvendo bug dos cantos
    if(bloco->j < (bloco->width/2))
        bloco->j = bloco->width/2;
    else if (bloco->j > COLUMNS - (bloco->width/2) - 1)
        bloco->j  = COLUMNS - (bloco->width/2) -1;
}

/*
    Verifica a colisao de Blocos
*/
int collisionDetect(char matrix[ROWS][COLUMNS], Bloco barra){
    int retorno = 0;

    if (!collisionDetect(matrix, barra))
        drawBar(matrix, barra, EMPY);

    //Colisao com a base
    if((barra.i + 1) >= ROWS)
           retorno = 1;
    //Colisao com a peça
    if (matrix [barra.i + 1][barra.j] != EMPY){
        retorno = 1;
    }
    int t2 = barra.width/2;
    if (matrix [barra.i + 1][barra.j+t2] != EMPY) {
        retorno = 1;
    }
    if (matrix [barra.i+ 1][barra.j-t2] != EMPY) {
        retorno = 1;
    }
    
    return retorno;
}

/*
    Verifica a colisao das Barras
*/

int collisionBar(char matrix[ROWS][COLUMNS], Bloco barra, int collideSides, int side){
    int retorno = 0;

    //Colisao com a base
    if((barra.i + 1) >= ROWS)
           retorno = 1;

     //Colisao com a base da barra com outras peças
    if (matrix [barra.i + 1][barra.j] != EMPY)
        retorno = 1;

    //Colisão base horizontal
    int t2 = barra.width/2;
    if (matrix [barra.i + 1][barra.j+t2] != EMPY) 
        retorno = 1;
    
    if (matrix [barra.i+ 1][barra.j-t2] != EMPY) 
        retorno = 1;
    
    //Colisão lateral horizontal
    if(collideSides==1){
        if(side==RIGHT && matrix[barra.i][barra.j + t2 + 1] != EMPY)
            retorno = 1;
        if(side==RIGHT && barra.j + t2 + 1 >= COLUMNS)
            retorno = 1;

        if(side==LEFT && matrix[barra.i][barra.j - t2 - 1] != EMPY)
            retorno = 1;
        if(side==LEFT && barra.j - t2 - 1 < 0)
            retorno = 1;
    }
    //Colisão lateral vertical
    if(collideSides==CHECK_SIDE &&
        (barra.orientacao == ORIENTACAO_UP ||
            barra.orientacao == ORIENTACAO_DOWN)){
        
        int i;
        for(i=0; i<barra.height; i++){
            //verificanfo colisão lateral com resto de outras peças
            if(side==RIGHT && matrix[barra.i - i][barra.j + 1] != EMPY)
                retorno = 1;
            
            if(side==LEFT && matrix[barra.i - i][barra.j - 1] != EMPY)
                retorno = 1;
        }
        }


    return retorno;
}