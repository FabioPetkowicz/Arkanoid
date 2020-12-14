// 2 Funções: StartBoard() e PrintBoard().
/*____________________________________________________________________________________________________________________________*/
#include <stdio.h>
#include <conio2.h>
//------------------------------------------------------------------------
#define     BLC         '@' //Bloco de Delimitação do Tabuleiro - Borda
//------------------------------------------------------------------------
#define     LIN_MTX     25  //Borda Inferior do Tabuleiro
#define     COL_MTX     29  //Borda Lateral do Tabuleiro
/*____________________________________________________________________________________________________________________________*/
//[1]
void StartBoard ( void ){
    int     i, j;
    char    mtx[LIN_MTX][COL_MTX];
    FILE    *fp;

    if (  ! ( fp = fopen ( "board.bin", "wb" )  )  ) printf("Erro-01-StartBoard\n");
    else{
        for ( i = 0; i < LIN_MTX; i++ )
            for ( j = 0; j < COL_MTX; j++ ){
                mtx[i][j] = ' ';
                if ( i == 0  ) mtx[i][j] = BLC;
                if ( i == LIN_MTX - 1 ) mtx[i][j] = BLC;
                if ( j == 0  ) mtx[i][j] = BLC;
                if ( j == COL_MTX - 2 ) mtx[i][j] = BLC;
                if ( j == COL_MTX - 1 ) mtx[i][j] = '\n';
                if ( j == COL_MTX - 1 ) mtx[LIN_MTX - 1][COL_MTX - 1] = EOF;
                fwrite ( &mtx[i][j] , sizeof ( char ), 1, fp );
            }
        //putc ( EOF, fp );
    }
    fclose ( fp );
}
//------------------------------------------------------------------------------------
//[2]
void PrintBoard ( void ){

    int     i, j;
    char    ch;
    FILE    *fp;

    if ( ! ( fp = fopen ( "board.bin", "rb" ) ) ) printf("Erro-02-PrintBoard\n");
    else{
        while( ! feof ( fp ) ){
            for ( i = 0; i < LIN_MTX; i++ )
                for ( j = 0; j < COL_MTX; j++ ){
                    fread ( &ch, sizeof ( char ), 1, fp );
                    textcolor ( WHITE );
                    printf("%c", ch);
            }
        }
        fclose ( fp );
    }
}
/*____________________________________________________________________________________________________________________________*/
