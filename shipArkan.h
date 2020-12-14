/*____________________________________________________________________________________________________________________________*/
#include <stdio.h>
#include <string.h>
//------------------------------------------------------------------
#define     BLC         '@'
//------------------------------------------------------------------
#define     SETA_E      75
#define     SETA_D      77
//------------------------------------------------------------------
#define     LIM_E       2   //Limite Esquerdo do Tabuleiro
#define 	LIM_D       27	//Limite Direito do Tabuleiro
//------------------------------------------------------------------
#define     X_SHIP      12
#define     Y_SHIP      24	//Ordenada da Nave e Limite para a Bola
//------------------------------------------------------------------
/*____________________________________________________________________________________________________________________________*/
/*____________________________________________________________________________________________________________________________*/
void StartShip ( char ship[ ], int *shipPos, char *shipSize ){

    int j;

    *shipSize = 'M';
    *shipPos = X_SHIP;

    for ( j = 0; j < 6; j++ ){
        ship[j] = BLC;
        if ( j == 5 ) ship[j] = '\0';
    }
}
//------------------------------------------------------------------
void StartPrintShip ( char ship[ ], int shipPos, char shipSize ){

    int j;

    if ( shipSize == 'M' ){
        for ( j = 0; j < 6; j++ ){
            ship[j] = BLC;
            if ( j == 5 ) ship[j] = '\0';
        }
    }
    else if ( shipSize == 'P' ){
        for ( j = 0; j < 4; j++ ){
            ship[j] = BLC;
            if ( j == 3 ) ship[j] = '\0';
        }
    }
    else if ( shipSize == 'G' ){
        for ( j = 0; j < 8; j++ ){
            ship[j] = BLC;
            if ( j == 7 ) ship[j] = '\0';
        }
    }
    gotoxy ( shipPos, Y_SHIP );
    printf("%s", ship );
}
//------------------------------------------------------------------
void PrintShip ( char ship[], int pos ){
//imprime a nave em qualquer posicao
    gotoxy ( pos, Y_SHIP );
    printf("%s", ship);

}
//------------------------------------------------------------------
void MoveShip ( char tecla, int *pos, char ship[] ){

    int shiplength;

    shiplength = strlen( ship ) -1 ;

    if ( tecla == SETA_E && *pos > LIM_E ){
        putchxy ( *pos + shiplength, Y_SHIP , ' ' );
       *pos = *pos - 1;
    }
	if ( tecla == SETA_D && *pos + shiplength < LIM_D ){
	    putchxy ( *pos, Y_SHIP, ' ' );
        *pos = *pos + 1;
	}
	PrintShip ( ship, *pos );
}
//------------------------------------------------------------------
void EraseShipPrint ( char ship[], int pos ){

    int   j, shiplength;

    shiplength = strlen ( ship );
    for ( j = 0; j < shiplength; j++ ){
        ship[j] = ' ';
    }
    gotoxy ( pos, Y_SHIP );
    printf("%s", ship );
}
//------------------------------------------------------------------
/*____________________________________________________________________________________________________________________________*/
