#include    <stdio.h>
#include    <conio2.h>
//------------------------------------------------------------------
#define		X_BALL	    14	//Absissa Inicial da Bola
#define		Y_BALL	    22  //Ordenada Inicial da Bola
//------------------------------------------------------------------
#define     INVERT      -1

void StartBallMovement( int *movementX , int *movementY ){

    *movementX = 1;
    *movementY = -1;

}
/*____________________________________________________________________________________________________________________________*/

void MoveBall ( char bola, int *x, int *y, int *movementX, int *movementY ){

    int     rastroX, rastroY;

    rastroX = *x;
    rastroY = *y;
    *x += *movementX;
    *y += *movementY;
    putchxy ( rastroX, rastroY, ' ');
    putchxy ( *x, *y, bola );

}
//------------------------------------------------------------------
void InvertMovementX ( int *movementX ){

    *movementX = *movementX * INVERT;

}
//------------------------------------------------------------------
void InvertMovementY ( int *movementY ){

    *movementY = *movementY * INVERT;
}
//------------------------------------------------------------------
/*____________________________________________________________________________________________________________________________*/

