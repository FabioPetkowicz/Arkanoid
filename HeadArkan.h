//Contém: Abertura(), Menu(), InstrucoesTxt(), le_texto();
#include <stdio.h>
#include <conio2.h>
#include <string.h> //para le_texto()

#define     BEEP        printf("\a")
void Abertura(void){
    textcolor ( LIGHTRED ); //codigo 12
    printf("\t_________________________________________________________________\n");
    printf("\t  IIII   IIIIII   II   II    IIII   II    II  IIIIII  II IIIII   \n");
    printf("\t II  II  II   II  II  II    II  II  III   II III  III II II   II \n");
    printf("\tIII  III II  II   II II    III  III II II II III  III II II    II\n");
    printf("\tIIIIIIII IIIIII   IIIII    IIIIIIII II  IIII III  III II II    II\n");
    printf("\tIII  III II  III  II  III  III  III II   III III  III II II   II \n");
    printf("\tIII  III II  IIII II   III III  III II    II  IIIIII  II IIIII   %c\n", 169);
    printf("\t_________________________________________________________________\n\n\n\n");

    textcolor ( WHITE );
    printf("\tTHE TIME AND ERA OF THIS STORY IS UNKNOWN.\n\n");
    printf("\tAFTER THE MOTHERSHIP \"ARKANOID\" WAS DESTROYED,\n\n");
    printf("\tA SPACECRAFT \"VAUS\" SCRAMBLED AWAY FROM IT.\n\n");
    printf("\tBUT ONLY TO BE TRAPPED IN SPACE WARPED BY SOMEONE...\n\n");
    printf("\t-----------------------------------------------------------------\n\n\n\n");
    textcolor ( LIGHTRED );
    printf("\t\t\t\tPress Any Key to Run");
    getch();
    clrscr();
    textcolor ( WHITE );
}
/*_________________________________________________________________________________________________________________________________________________________________ */
char Menu ( void ){

    char option;

    do{
        textcolor ( WHITE );
        printf("***ARKANOID%c", 169);
        printf("***\n   The Game\n");
        printf("    -Menu-\n(1)Start\n(2)Ranking\n(3)Instrucoes\n(4)Exit\n");
        option = getche();
        if ( option != '1' &&  option != '2' && option != '3' && option != '4' ){ clrscr(); BEEP; }
    }while ( option != '1' &&  option != '2' && option != '3' && option != '4' );

    textcolor ( LIGHTGRAY );
    return option;
}
/*_________________________________________________________________________________________________________________________________________________________________ */
void Instrucoes( void ){

        printf("_________________________________________________________________\n");
        printf("  IIII   IIIIII   II   II    IIII   II    II  IIIIII  II IIIII   \n");
        printf(" II  II  II   II  II  II    II  II  III   II III  III II II   II \n");
        printf("III  III II  II   II II    III  III II II II III  III II II    II\n");
        printf("IIIIIIII IIIIII   IIIII    IIIIIIII II  IIII III  III II II    II\n");
        printf("III  III II  III  II  III  III  III II   III III  III II II   II \n");
        printf("III  III II  IIII II   III III  III II    II  IIIIII  II IIIII   %c\n", 169);
        printf("_________________________________________________________________\n\n\n");
        textcolor( YELLOW );
		printf("_______________ARKANOID - INSTRUCOES________________________________\n");
		printf("Tecla Esc     ( Esc ) - Encerra o jogo a qualquer momento.\n\n");
		//printf("Tecla S       ( S ) - Salva o Estado do Jogo\n");
		//printf("Tecla L       ( L ) - Carrega o Estado do Jogo\n");
		printf("Seta Direita  ( -> )  - Movimenta a Vaus uma posicao para a Direita\n\n");
		printf("Seta Esquerda ( <- )  - Movimenta a Vaus uma posicao para a Esquerda\n");
		printf("____________________________________________________________________\n");
		textcolor ( LIGHTGRAY );
		printf("Digite qualquer tecla para Sair\n");
        getch();
        clrscr();
}

/*_________________________________________________________________________________________________________________________________________________________________ */
void InstrucoesTxt( void ){

	FILE	*fp;

	if ( ! ( fp = fopen ( "ARKANOID INSTRUCOES.txt", "w" ) ) )	printf("ERRO AO CRIAR README.TXT\n");
	else{
        fprintf( fp, "_________________________________________________________________\n");
        fprintf( fp, "  IIII   IIIIII   II   II    IIII   II    II  IIIIII  II IIIII   \n");
        fprintf( fp, " II  II  II   II  II  II    II  II  III   II III  III II II   II \n");
        fprintf( fp, "III  III II  II   II II    III  III II II II III  III II II    II\n");
        fprintf( fp, "IIIIIIII IIIIII   IIIII    IIIIIIII II  IIII III  III II II    II\n");
        fprintf( fp, "III  III II  III  II  III  III  III II   III III  III II II   II \n");
        fprintf( fp, "III  III II  IIII II   III III  III II    II  IIIIII  II IIIII   %c\n", 169);
        fprintf( fp, "_________________________________________________________________\n\n\n");
		fprintf( fp, "_______________ARKANOID - INSTRUCOES________________________________\n");
		fprintf( fp, "Tecla Esc     ( Esc ) - Encerra o jogo a qualquer momento.\n");
		//fprintf( fp, "Tecla S       ( S ) - Salva o Estado do Jogo\n");
		//fprintf( fp, "Tecla L       ( L ) - Carrega o Estado do Jogo\n");
		fprintf( fp, "Seta Direita  ( -> )  - Movimenta a Vaus uma posicao para a Direita\n");
		fprintf( fp, "Seta Esquerda ( <- )  - Movimenta a Vaus uma posicao para a Esquerda\n");
		fprintf( fp, "____________________________________________________________________\n");
		fclose ( fp );
	}
}
/*_________________________________________________________________________________________________________________________________________________________________ */
void le_texto ( char texto[ ], int size_texto ){ // string: ponteiro implícito

    char dummy[size_texto + 1]; // cabe um caractere a mais do que no texto:

    fflush ( stdin );
    fgets ( dummy, sizeof( dummy ), stdin ); // lê caracteres

    // O último caractere tem que ser '\n' para estar correto:
    while( dummy[strlen(dummy) - 1] != '\n' ){

        printf("\nNumero de caracteres digitados excedeu tamanho do campo.\n");
        printf("Numero maximo de caracteres eh %d.\n", size_texto - 1);
        printf("Digite o conteudo novamente.\n");
        fflush (stdin);
        fgets(dummy, sizeof(dummy), stdin); // lê caracteres novamente
    }

    dummy[strlen(dummy)-1]= '\0'; // sempre precisa substituir o '\n'
    strcpy(texto, dummy); // transfere conteúdo digitado e sem o '\n' para texto
}
/*_________________________________________________________________________________________________________________________________________________________________ */
