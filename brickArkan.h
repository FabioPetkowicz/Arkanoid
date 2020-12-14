#include    <stdio.h>
#include    <string.h>
#include    <conio2.h>
#include    "HeadArkan.h" // le_texto
//------------------------------------------------------------------
#define     SETA_E      75
#define     SETA_D      77
//------------------------------------------------------------------
#define     LIN_BRK         10
#define     COL_BRK         13
//------------------------------------------------------------------
#define     LIM_E           2   //Limite Esquerdo do Tabuleiro
#define 	LIM_D           27	//Limite Direito do Tabuleiro
#define		LIM_SUP         2	//Limite Superior do Tabuleiro
#define		LIM_INF         23	//Limite Inferiror do Tabuleiro
//---------------------------------------------------------------------------------
#define     LIMIT_LIN       50
#define     POS_BRK         2   //Coluna Inicial de Impressao da Matriz de Tijolos
//---------------------------------------------------------------------------------
#define		SZ_SHIP     8   //Tamanho da String Nave + '\0'
#define     SZ_NAME     21
#define     N_PLAYERS   10
/*____________________________________________________________________________________________________________________________*/
typedef struct{
    int         mtx[LIN_BRK][COL_BRK];
    int         lin, col;
    int         x, y;
    int         level; //salva a linha lida --> ver como avançar, linha-a-linha, dentro do arquivo
}TIJOLOS;

/*____________________________________________________________________________________________________________________________*/

typedef struct{
	char		bola;
    int         x, y;
    int         movementX, movementY;
	int			velo;
}BOLA;
/*____________________________________________________________________________________________________________________________*/
typedef struct{
    char        vaus[SZ_SHIP]; // SZ_SHIP = 8
	int			pos;
	char        size; //P, M, G
}NAVE;
//------------------------------------------------------------------------------------------------
typedef struct{
    char        name[SZ_NAME];
    int         lifes;
    int         points;
}JOGADOR;
/*____________________________________________________________________________________________________________________________*/

void StartBrick ( int  brickmtx[][COL_BRK] ){

    FILE    *fp;
    char    brick_line[LIN_BRK][LIMIT_LIN];
    int     i, j, col, y;

    if ( ! ( fp = fopen( "brick.txt", "r" ) ) ) printf("Erro01 - Abertura bricks.txt\n");
    else{
        for ( i = 0; i < LIN_BRK; i++ ){ //lê 10 linhas do Arquivo Brick e descarrega na Mtz brick_line
            fgets ( brick_line[i], sizeof( brick_line ), fp );
            brick_line[i][COL_BRK] = '\0';

        }
        fclose ( fp );
//monta a matriz de tijolos, representada por inteiros, a partir da mtz de caracteres lida do arquivo texto
        for ( i = 0; i < LIN_BRK; i++ )
            for ( j = 0; j < COL_BRK; j++ ){
                if ( brick_line[i][j] == 'X' ) brickmtx[i][j] = 1;

                if ( brick_line[i][j] == 'Y' ) brickmtx[i][j] = 2;

                if ( brick_line[i][j] == 'Z' ) brickmtx[i][j] = 3;
            }
        }
}
/*____________________________________________________________________________________________________________________________*/
void PrintBrickMtx ( int brickmtx[][COL_BRK] ){

    int i, j, y;

    for ( i = 0, y = 2; i < 10; i++, y++ ){
        gotoxy ( 2 , y );
        for ( j = 0; j < COL_BRK; j++ ){
            if ( brickmtx[i][j] == 0 ) printf("  ");
            if ( brickmtx[i][j] == 1 ){
                textcolor( YELLOW );
                printf("##");
                textcolor( WHITE );
            }
            if ( brickmtx[i][j] == 2 ){
                textcolor( CYAN );
                printf("##");
                textcolor( WHITE );
            }
            if ( brickmtx[i][j] == 3 ){
                textcolor ( LIGHTRED );
                printf("##");
                textcolor( WHITE );
            }
        }
    }
}
/*____________________________________________________________________________________________________________________________*/
int ExisteTijolo( int brickmtx[][COL_BRK] ){

	int existe, i, j;

	i = j = existe = 0;
	do{
		if( brickmtx[i][j] != 0 ) existe = 1;
		j++;
		if ( j == COL_BRK - 1 ){
			j = 0;
			i++;
		}
	}while ( existe == 0 && i < 10 );
	return existe;
}
/*______________________________________________________________________________________________________________________________*/
void DecBrick (  int brickmtx[][COL_BRK], int brickLin, int brickCol, int *points ){

    if ( brickmtx[brickLin][brickCol] > 0 ){
        brickmtx[brickLin][brickCol] = brickmtx[brickLin][brickCol]--;
        *points = *points + 10;
    }
}
/*______________________________________________________________________________________________________________________________*/
void ReprintBrick ( int brickmtx[][COL_BRK], int brickLin, int brickCol, int brickX, int brickY ){

    if ( brickX % 2 == 0 ){
        if ( brickmtx[brickLin][brickCol] == 0 ){ gotoxy ( brickX, brickY ); printf("  "); }
    }
    else{
        if ( brickmtx[brickLin][brickCol] == 0 ){ gotoxy ( brickX - 1, brickY ); printf("  "); }
    }

}
/*______________________________________________________________________________________________________________________________*/
char EvalCrash_Inf_Asc( int *x ){
//Área Inferior - Bola na Ascendente
    char    crash = 'G';

    if ( *x == LIM_E || *x == LIM_D ) crash = 'L';
    return crash;
}
/*______________________________________________________________________________________________________________________________*/
char EvalCrash_Inf_Desc( int *ballx, int *bally, char ship[], int shipPos ){
//Área Inferior - Bola na Descendente
    int     shiplength;
    char    crash = 'G';

    if ( *ballx == LIM_E || *ballx == LIM_D ) crash = 'L';
    else if ( *bally == LIM_INF ){
        crash = 'F';
        shiplength = strlen ( ship ) - 1;
        while ( shiplength >= 0 && crash == 'F' ){
            if ( *ballx == shipPos + shiplength ) crash = 'V';
            shiplength--;
        }
    }
    return crash;
}
/*______________________________________________________________________________________________________________________________*/
char EvalCrash_Sup_ADir ( int brickmtx[][COL_BRK], int *brickLin, int *brickCol, int *brickX, int *brickY, BOLA ball ){
//Ascendente à Direita ( x = 1, y = -1)
    char    crash = 'G';

    if ( ball.x < LIM_D ){
            if ( ball.y > LIM_SUP && brickmtx[ball.y - 3][ball.x/2] > 0 ){ //Tijolo Acima
                crash = 'T';
                *brickLin = ball.y - 3;
                *brickCol = ball.x/2;
                *brickY = ball.y - 1;
                *brickX = ball.x;
            }
            else if ( ball.y > LIM_SUP && brickmtx[ball.y - 3][ball.x/2 + 1] > 0 ){ //Tijolo na Diagonal
                crash = 't';
                *brickLin = ball.y - 3;
                *brickCol = ball.x/2 + 1;
                *brickY = ball.y - 1;
                *brickX = ball.x + 1;
            }
            else if ( ball.y == LIM_SUP )    crash = 'S'; //Teto
    }
    else{ //se ( ball.x == LIM_D == 27 )
        if ( ball.y > LIM_SUP ){
            if ( brickmtx[ball.y - 3][ball.x/2] > 0 ){ //Tijolo Acima e LIM_D
                crash = 'c';
                *brickLin = ball.y - 3;
                *brickCol = ball.x/2;
                *brickY = ball.y - 1;
                *brickX = ball.x - 1;
            }
            else  crash = 'L';
        }
        else if ( ball.y == LIM_SUP ) crash = 'C';
    }
    return crash;
}
/*______________________________________________________________________________________________________________________________*/
char EvalCrash_Sup_AEsq( int brickmtx[][COL_BRK], int *brickLin, int *brickCol, int *brickX, int *brickY, BOLA ball ){
//Ascendente à Esquerda ( x = -1; y = -1 )
    char    crash = 'G';

    if ( ball.x > LIM_E ){// ( ball.x > 2 )
            if ( ball.y > LIM_SUP && brickmtx[ball.y - 3][ball.x/2] > 0 ){ //Tijolo
                crash = 'T';
                *brickLin = ball.y - 3;
                *brickCol = ball.x/2;
                *brickY = ball.y - 1;
                *brickX = ball.x;
            }
            else if ( ball.y > LIM_SUP && brickmtx[ball.y - 3][ball.x/2 - 1] > 0 ){ //Tijolo na Diagonal
                crash = 't';
                *brickLin = ball.y - 3;
                *brickCol = ball.x/2;
                *brickY = ball.y - 1;
                *brickX = ball.x;
            }
            else if ( ball.y == LIM_SUP )    crash = 'S'; //Teto
    }
    else{ //se ( ball.x == LIM_E == 2 )
        if ( ball.y > LIM_SUP && brickmtx[ball.y - 3][0] > 0 ){ //Tijolo Acima //ball.x/2 - 1 == 0
            crash = 'c';
            *brickLin = ball.y - 3;
            *brickCol = 0; // 0 == ball.x - 2 == LIM_E - 2 == 0
            *brickY = ball.y - 1;
            *brickX = ball.x;
        }
        else if ( ball.y > LIM_SUP )  crash = 'L';
        else if ( ball.y == LIM_SUP ) crash = 'C';
    }
    return crash;
}
/*______________________________________________________________________________________________________________________________*/
char EvalCrash_Sup_DDir( int brickmtx[][COL_BRK], int *brickLin, int *brickCol, int *brickX, int *brickY, BOLA ball ){
//Descendente à Direita ( x = 1, y = 1 )
    char    crash = 'G';

    if ( ball.x < LIM_D - 1 ){ // ( ball.x < 26 )
        if ( brickmtx[ball.y - 1][ball.x/2] != 0 ){ //Tijolo Abaixo
            crash = 'T';
            *brickLin = ball.y - 1;
            *brickCol = ball.x/2;
            *brickY = ball.y + 1;
            *brickX = ball.x;
        }
		//inserir t aqui
    }
    else{ //se ( ball.x >= LIM_D - 1 ) // ( ball.x >= 26 )
        if ( ball.x == LIM_D && brickmtx[ball.y - 1][ball.x/2] != 0 ){ //Tijolo Abaixo e LIM_D
            crash = 'c';
            *brickLin = ball.y - 1;
            *brickCol = ball.x/2;
            *brickY = ball.y + 1;
            *brickY = ball.x;
        }
        else if ( ball.x == LIM_D - 1 && brickmtx[ball.y - 1][ball.x/2] != 0 ){
            crash = 'T';
            *brickLin = ball.y - 1;
            *brickCol = ball.x/2;
            *brickY = ball.y + 1;
            *brickX = ball.x;
        }
        else if ( ball.x == LIM_D ) crash = 'L';
    }
    return crash;
}
/*____________________________________________________________________________________________________________________________*/
char EvalCrash_Sup_DEsq( int brickmtx[][COL_BRK], int *brickLin, int *brickCol, int *brickX, int *brickY, BOLA ball ){
//Descendente para Esquerda//( x = -1; y = -1 )
    char    crash = 'G';

    if ( ball.x > LIM_E ){ // ( ball.x > 2 )
            if ( brickmtx[ball.y - 1][ball.x/2] != 0 ){
                crash = 'T';
                *brickLin = ball.y - 1;
                *brickCol = ball.x/2;
                *brickY = ball.y + 1;
                *brickX = ball.x;
            }
			//inserir t aqui
        }
        else{
            if ( ball.x == LIM_E ){
                if ( brickmtx[ball.y - 1][ball.x/2 - 1] != 0 ){
                    crash = 'c';
                    *brickLin= ball.y - 1;
                    *brickCol= ball.x/2 - 1;
                    *brickY = ball.y + 1;
                    *brickX = ball.x;
                }
                else crash = 'L';
            }
        }
        return crash;
}

void ExibeVidas ( int vidas ){

    gotoxy( 34, 4 );
    textcolor ( WHITE );
    printf("Life: %d\n", vidas );

}
void ExibeLevel ( int level ){

    textcolor( WHITE );
    gotoxy( 34, 6 );
    printf("Level: %2d\n", level );

}
void ExibePontos ( int pontos ){

    textcolor( WHITE );
    gotoxy( 34, 8 );
    printf("Points: %2d\n", pontos );

}

void lista_ranking ( void ){

    JOGADOR player;
	FILE    *arq;
    int     i = 1;

	if( ! ( arq = fopen( "hiscore.bin" , "rb" ) ) )	printf("\nErro03-Leitura de hiscore.bin\n");
	else{
	    textcolor( YELLOW );
		printf("_______________RANKING_______________\n\n"); //37 caracteres <15 + ranking + 15>
		while( ! feof( arq ) ){
            if( fread ( &player, sizeof( JOGADOR ), 1, arq ) == 1 )
                if ( player.points > 0 ){
                    printf("%2d. - %10d - %s\n\n", i, player.points, player.name );
                    i++;
                }
		}
	}
	printf("_____________________________________\n");
    textcolor ( LIGHTGRAY );
	fclose( arq );
	printf("Digite qualquer tecla para Sair\n");
	getch();
	clrscr();
}

void Ordena ( JOGADOR players[], int tam ){

    int     i, troca;
    JOGADOR   aux;

    do{
        for ( i = 0, troca = 0; i < tam - 1; i++ )
            if ( players[i].points < players[i+1].points ){
                aux = players[i];
                players[i] = players[i+1];
                players[i+1] = aux;
                troca = 1;
            }
    }while ( troca == 1 );
}

void inserir_ordenadamente ( JOGADOR player ){

	FILE        *arq;
	JOGADOR     players[N_PLAYERS+1];
	int         i, tam;

	if( ! ( arq = fopen( "hiscore.bin", "r+b" ) ) ) printf("\nErro05-Abertura de Escrita hiscore.bin\n");
	else{
	    i = 0;
	    while ( ! feof ( arq ) ){
            fread ( &players[i], sizeof( JOGADOR ), 1, arq );
            i++;
	    }
        tam = i - 1;
        if ( player.points > players[tam - 1].points ){
                printf("\nCongratulations!!!");
                printf("\nName: ");   le_texto ( player.name, sizeof ( player.name ) );
                players[tam - 1] = player;
                Ordena ( players, tam );
                rewind ( arq );
                for ( i = 0; i < tam ; i++ )
                    fwrite ( &players[i], sizeof( JOGADOR ), 1, arq );
        }
        fclose( arq );
        clrscr();
    }
}
/*_____________________________________________________________________________________________________________________________*/

//Funções Antigas



/*
char EvalCrash_Inf_Desc( char tecla1, int *ballx, int *bally, int *movementX, NAVE *ship ){
//Área Inferior - Bola na Descendente
    int     length, meio;
    char    crash = 'G';

    if ( *ballx == LIM_E || *ballx == LIM_D ) crash = 'L';
    else if ( *bally == LIM_INF ){
        crash = 'F';
        if ( ship->size == 'M' ){ length = 4; meio = 2; }
        else if ( ship->size == 'P' ){ length = 2; meio = 1; }
        else if ( ship->size == 'G' ){ length = 6; meio = 3; }

        if ( *ballx == ship->pos + meio ){
            crash = 'v'; //centro da Vaus, movementX = 0; movementY = -1;
            return crash;
        }
        else{
            while ( length >= 0 && crash == 'F' ){
                if ( *ballx == ship->pos + length ) crash = 'V';
                length--;
            }
            if ( crash == 'V' && *movementX != 0 ) return crash;
            else{
                if ( tecla1 == SETA_D ) *movementX = -1; //sofrerá inversão // no case 'V':
                else *movementX = 1;
            }
        }
    }
    return crash;
}
*/
