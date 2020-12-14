/*__________________________________________________________________________________________________________________________________________________________________*/
#include    <stdio.h>
#include    <conio2.h>
#include    <windows.h>
#include    "ballArkan.h"
#include    "brickArkan.h"
#include    "shipArkan.h"
#include    "boardArkan.h"
/*_________________________________________________________________________________________________________________________________________________________________ */
#define     BEEP        printf("\a")
#define     _NOCURSOR   0   //
//------------------------------------------------------------------------
#define     ESC         27  //tecla Esc
#define     SETA_E      75  //tecla Seta Esquerda
#define     SETA_D      77  //tecla Seta Direita
//------------------------------------------------------------------------
#define     ENTER       13  // tecla Enter
//------------------------------------------------------------------------
#define     LIN_MTX     25  //Borda Inferior do Tabuleiro
#define     COL_MTX     29  //Borda Lateral do Tabuleiro
//------------------------------------------------------------------------
#define     LIN_BRK     10  //Linhas de Tijolos
#define     COL_BRK     13  //Colunas de Tijolos
//------------------------------------------------------------------------
#define     X_SHIP      12  //Absissa Inicial de Impressao da Nave
#define     Y_SHIP      24	//Ordenada da Nave e Limite para a Bola
#define		SZ_SHIP     8   //Tamanho Limite(7) da String ship + 1
//------------------------------------------------------------------------
#define		X_BALL	    14	//Absissa Inicial da Bola
#define		Y_BALL	    22  //Ordenada Inicial da Bola
//------------------------------------------------------------------------
#define     BLC         '@' //Caracter de Delimitação do tabuleiro
#define     SZ_NAME     21  //Tamanho da String name + 1
// Funcao Game_______________________________________________________________

void Game( void ){

    NAVE		ship = { "@@@@@", X_SHIP, 'M' };
    BOLA        ball = { 'O', X_BALL, Y_BALL, 1, -1, 300 }; // velo ideal de 350 até 220
    TIJOLOS     brick = { {0}, 0, 0, 2, 2, 1 };
    JOGADOR     player = {"\0", 3, 0 };

    char    	tecla1, tecla2, crash;

/*-----------------------------------------------------------------------------------------------*/
//impressao inicial das pecas
    StartBrick ( brick.mtx );
    PrintBoard( );
    PrintBrickMtx( brick.mtx );
    PrintShip ( ship.vaus, ship.pos );
    putchxy ( ball.x, ball.y, ball.bola );
/*--------------------------------------------------------------------*/
    ExibeVidas ( player.lifes );
    ExibeLevel( brick.level );
    ExibePontos( player.points );
/*--------------------------------------------------------------------*/

    while ( tecla1 != ESC && player.lifes > 0){

        _setcursortype(_NOCURSOR);
        if ( kbhit() ){
            tecla1 = getch();
            if ( tecla1 == -32 || tecla1 == 0 ){
                tecla2 = getch();
                tecla1 = tecla2;
            }
            if ( tecla1 == SETA_E ) MoveShip ( tecla1, &ship.pos, ship.vaus );
            else if ( tecla1 == SETA_D ) MoveShip ( tecla1, &ship.pos, ship.vaus );
        }

        Sleep ( ball.velo );
            MoveBall ( ball.bola, &ball.x, &ball.y, &ball.movementX, &ball.movementY );

            if ( ExisteTijolo( brick.mtx ) ){
//Área Inferior - Ascendente
                if ( ball.y >= LIN_BRK + 3 && ball.movementY < 0 )
                    crash = EvalCrash_Inf_Asc( &ball.x );

//Área Inferior - Descendente
                else if ( ball.y >= LIN_BRK + 1 && ball.movementY > 0 )
                    crash = EvalCrash_Inf_Desc ( &ball.x, &ball.y, ship.vaus, ship.pos );

//Área Superior - Ascendente a Direita //( x = 1; y = -1 )
                else if ( ball.y <= LIN_BRK + 2 && ball.movementX > 0 && ball.movementY < 0 )
                    crash = EvalCrash_Sup_ADir( brick.mtx, &brick.lin, &brick.col, &brick.x, &brick.y, ball );

//Área Superior - Ascendente a Esquerda //( x = -1; y = -1 )
                else if ( ball.y <= LIN_BRK + 2 && ball.movementX < 0 && ball.movementY < 0 )
                    crash = EvalCrash_Sup_AEsq( brick.mtx, &brick.lin, &brick.col, &brick.x, &brick.y, ball );

//Área Superior - Descendente a Direita //( x = 1; y = 1 )
                else if ( ball.y < LIN_BRK + 1 && ball.movementX > 0 && ball.movementY > 0 )
                    crash = EvalCrash_Sup_DDir( brick.mtx, &brick.lin, &brick.col, &brick.x, &brick.y, ball );

//Área Superior - Descendente a Esquerda//( x = -1; y = 1 )
                else if ( ball.y < LIN_BRK + 1 && ball.movementX < 0 && ball.movementY > 0 )
                    crash = EvalCrash_Sup_DEsq( brick.mtx, &brick.lin, &brick.col, &brick.x, &brick.y, ball );
            }

            switch ( crash ){

                case 'G': //segue movimento
                    break;

                case 't': //Tijolo na Diagonal
                case 'c': //cantinho entre tijolo e parede
                    InvertMovementX ( &ball.movementX );
                    InvertMovementY ( &ball.movementY );
                    DecBrick ( brick.mtx, brick.lin, brick.col, &player.points );
                    ReprintBrick( brick.mtx, brick.lin, brick.col, brick.x, brick.y );
                    ExibePontos( player.points );
                    break;

                case 'C': //Corner - Canto Superior
                    InvertMovementX ( &ball.movementX );
                    InvertMovementY ( &ball.movementY );
                    break;

                case 'L': //Lateral do Tabuleiro
                    InvertMovementX ( &ball.movementX );
                    break;

                case 'T': //Tijolo
                    InvertMovementY ( &ball.movementY );
                    DecBrick ( brick.mtx, brick.lin, brick.col, &player.points );
                    ReprintBrick ( brick.mtx, brick.lin, brick.col, brick.x, brick.y );
                    ExibePontos( player.points );
                    ball.velo = ball.velo + 5;
                    break;

                case 'S': //Superior Limite - Teto
                    InvertMovementY ( &ball.movementY );
                    break;

                case 'V': //Vaus
                    InvertMovementY ( &ball.movementY );

                    break;
/*
                case 'v': //Centro da Vaus
                    ball.movementX = 0;
                    InvertMovementY ( &ball.movementY );
                    break;
*/
                case 'F': //Fora
                    BEEP;
                    EraseShipPrint ( ship.vaus, ship.pos );
                    StartShip ( ship.vaus, &ship.pos, &ship.size );
                    putchxy ( ball.x, ball.y, ' ');
                    ball.x = X_BALL;
                    ball.y = Y_BALL;
                    PrintShip ( ship.vaus, ship.pos );
                    putchxy ( ball.x, ball.y, ball.bola );
                    StartBallMovement ( &ball.movementX, &ball.movementY );
                    player.lifes--;
                    ExibeVidas( player.lifes );
                    BEEP;
                    Sleep (25);

                    break;
            }
    } //FIM DO LAÇO DE JOGO
    clrscr();
    if ( player.lifes == 0 ){
        gotoxy ( 5, 12 );
        printf("GAME OVER");
        BEEP;
        Sleep(10);
        BEEP;
        Sleep(10);
        BEEP;
    }
    clrscr();
    inserir_ordenadamente( player );
}
