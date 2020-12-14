/*__________________________________________________________________________________________________________________________________________________________________*/
#include    <stdio.h>
#include    <conio2.h>
#include    <windows.h>
#include    "Game.h"

/*__________________________________________________________________________________________________________________________________________________________________*/
void main()
{
    char    	option;
/*--------------------------------------------------------------------------------*/
//Abertura do Jogo + Menu Inicial
    Abertura();
    InstrucoesTxt();
    do{
        option = Menu();

        switch ( option ){

            case '1': //JOGO ARKANOID
                clrscr();
                printf("\n\n\tGame\n");
                //Sleep ( 1000 );
                clrscr();
                gotoxy ( 1, 1 );
                Game();
                break;

            case '2': //RANKING
                clrscr();
                printf("\n\n\tRanking\n");
                Sleep ( 1000 ); clrscr();
                lista_ranking();
                break;

            case '3': //INSTRUCOES
                clrscr();
                printf("\n\n\tInstrucoes\n");
                Sleep ( 1000 ); clrscr();
                Instrucoes();
                break;

            case '4': // SAIR
                clrscr();
                printf("\n\n\tGoodbye!\n");
                Sleep ( 500 ); clrscr();
                break;

        }

    }while ( option != '4' );
}
/*____________________________________________________________________________________________________________________________*/
