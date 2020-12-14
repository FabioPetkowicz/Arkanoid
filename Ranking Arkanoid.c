#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include "HeadArkan.h"

#define SZ_NAME 21
#define N_PLAYERS 10

typedef struct{
    char    name[SZ_NAME];
    int     points;
}JOGADOR;


int     menu(void);
void    criar_arq( void );
void    lista_ranking (JOGADOR player);
void    inserir_jogador (JOGADOR player);

void Ordena ( JOGADOR players[], int tam );
void inserir_ordenadamente ( JOGADOR player );

int main()
{
	JOGADOR     player;
    int op;

	do{
		op = menu();
		switch(op)
		{
			case 1: criar_arq();
				break;
			case 2: lista_ranking ( player );
				break;
			case 3: inserir_jogador ( player );
				break;
			case 4: inserir_ordenadamente( player );
				break;
            case 5:
                break;
		}
	}while ( op!= 5 );

	return 0;
}

int menu ( void )
{
    int opc;

	do{
		printf("(1)Criar Ranking\n");
		printf("(2)Listar Ranking\n");
		printf("(3)Inserir Jogador\n");
		printf("(4)Insere Ordenado\n");
		printf("(5)Sair\n");
		scanf("%d", &opc );
		if ( opc < 1 && opc > 5 ) clrscr();
    } while ( opc < 1 && opc > 5 );

    return opc;
}

void criar_arq ( void ){

    int         i;
	FILE	    *arq;
    JOGADOR     playerbuffer = { "\0", 0 };

	if ( ! ( arq = fopen ( "hiscore.bin" , "wb") ) ) printf("\nErro01-Criar hiscore.bin\n");
	else{
        for ( i = 0; i < 10; i++ )
            fwrite ( &playerbuffer, sizeof( JOGADOR ), 1, arq );
        fclose( arq );
	}
}

void lista_ranking ( JOGADOR player ){

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
}

void inserir_jogador ( JOGADOR player ){ //lê um registro por vez

	FILE    *arq;

	printf("\nINSERIR Jogador\n");
	if( ! ( arq = fopen("hiscore.bin", "ab") ) ) printf("\nErro04-Abertura para Insercao de Jogador\n");
	else{
        printf("\nName: "); le_texto ( player.name, sizeof ( player.name ) );
        printf("\nPoints: "); scanf( "%d", &player.points );
        printf("\n");
        if( fwrite ( &player, sizeof( JOGADOR ), 1, arq ) != 1)	printf("\nErro05-Escrita em hiscore.bin\n");
    }
	fclose( arq );
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
	JOGADOR     players[N_PLAYERS+1], playerbuffer;
	int         i, tam;

	printf("\nINSERIR Ordenadamente\n");
	if( ! ( arq = fopen( "hiscore.bin", "r+b" ) ) ) printf("\nErro05-Abertura de Escrita hiscore.bin\n");
	else{
	    printf("\nName: ");   le_texto ( playerbuffer.name, sizeof ( player.name ) );
        printf("\nPoints: "); scanf( "%d", &playerbuffer.points );
        printf("\n");
	    i = 0;
	    while ( ! feof ( arq ) ){
            fread ( &players[i], sizeof( JOGADOR ), 1, arq );
            //players[i] = player;                            //Salva num Vetor
            i++;
	    }
        tam = i - 1;
        if ( playerbuffer.points > players[tam - 1].points ){
                players[tam - 1] = playerbuffer;
                Ordena ( players, tam );
                rewind ( arq );
                for ( i = 0; i < tam ; i++ )
                    fwrite ( &players[i], sizeof( JOGADOR ), 1, arq );
        }
        fclose( arq );
    }
}

