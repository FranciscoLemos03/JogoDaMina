#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Estrutura "celula" que vai ter:
	eBomba: V ou F
	foiAberta: V ou F
	vizinhos: 0 a 8
*/
typedef struct{
	int eBomba;
	int foiAberta;
	int vizinhos;
}Celula;

//var globais
int l, c;
Celula jogoFacil[8][10];
int tamLinhasFacil = 8;
int tamColunasFacil = 10;

// procedimento para iniciar a matriz do jogo

int main() {
	
	menuJogo();
	
	return 0;
}

// procedimento para o menu principal
void menuJogo() {
	// sera usada como condicao para que o laço DO WHILE ocorra. Assim, caso o usuario digite 0, ele vai sair do programa. 
	// Caso ele digite qualquer outro numero, a opcao ? tratada pelo teste condicional SWITCH.	
    int continuar=-1;
    int aux=-1;
    do {
        system("cls || clear");
        printf("-------------------------------\n");
        printf("\n\tJogo da Mina\n\n");
        printf("-------------------------------\n");
        printf("1. Jogar\n");
        printf("0. Sair\n");
        printf("-------------------------------\n");

        do
        {
            fflush(stdin);
            if(scanf("%d", &aux) != 0){
                continuar = aux;
            }
            if(continuar < 0 || continuar > 1) {
                system("cls || clear");
                printf("erro, opcao invalida!\n\n");
                
                printf("-------------------------------\n");
        		printf("\n\tJogo da Mina\n\n");
		        printf("-------------------------------\n");
        		printf("1. Jogar\n");
       			printf("0. Sair\n");
       		 	printf("-------------------------------\n");
            }
            
        } while(continuar < 0 || continuar > 1 );

        switch(continuar)
        {
            case 1:
                jogarFacil();
                break;
                
            case 0:
                printf("\nXau e um bolicao");
                break;

            default:
                printf("Digite uma opcao valida\n");
                break;
            
        }

        printf("\n");
        system("pause");
        
    } while(continuar != 0);
}

// procedimento para jogar o jogo no modo facil
void jogarFacil() {
	iniciarJogoFacil();
	sortearBombasFacil();
	contarBombasFacil();
	printf("\n\t      Jogo da Mina | Modo Facil\n");
	lerCoordsFacil();
}

// procedimento para iniciar o jogo
void iniciarJogoFacil() {

	for(l = 0; l < tamLinhasFacil; l++) {
		for(c = 0; c < tamColunasFacil; c++) {
			//iniciar o jogo
			jogoFacil[l][c].eBomba = 0;
			jogoFacil[l][c].foiAberta = 0;
			jogoFacil[l][c].vizinhos = 0;
		}
	}
}

// procedimento para sortear bombas 
void sortearBombasFacil() {
	int i, nrBombas = 10;
	srand(time(NULL));
	for(i = 1; i <= nrBombas; i++) {
		l = rand() % tamLinhasFacil;
		c = rand() % tamColunasFacil;
		if(jogoFacil[l][c].eBomba == 0) {
			jogoFacil[l][c].eBomba = 1;
		}else
			i--;
	}
	
}

//função que vai mostrar se um par de coords é valido ou nao(1 -> Valido, 0 -> Invalido)
int coordenadaValidaFacil(int l, int c) {
	if(l >= 0 && l < tamLinhasFacil && c >= 0 && c < tamColunasFacil){
		return 1;
	} else {
		return 0;
	}
}

// função que vai retorar a quantidade de bombas vizinhas de l c
int quantBombasVizinhasFacil(int l, int c){
	// N l-1 c
	// S l+1 c
	// E l c-1
	// O l c+1
	// NE l-1 c-1
	// NO l-1 c+1
	// SE l+1 c-1
	// SO l+1 c+1
	
	int quantidade = 0;
	
	if(coordenadaValidaFacil(l - 1, c) && jogoFacil[l-1][c].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l + 1, c) && jogoFacil[l+1][c].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l, c - 1) && jogoFacil[l][c-1].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l, c + 1) && jogoFacil[l][c+1].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l - 1, c - 1) && jogoFacil[l-1][c-1].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l - 1, c + 1) && jogoFacil[l-1][c+1].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l + 1, c - 1) && jogoFacil[l+1][c-1].eBomba) {
		quantidade++;
	} if(coordenadaValidaFacil(l + 1, c + 1) && jogoFacil[l+1][c+1].eBomba) {
		quantidade++;
	}
	
	return quantidade;	
}

// procedimento para contar as bombas vizinhas
void contarBombasFacil(){
	for(l = 0; l < tamLinhasFacil; l++) {
		for(c = 0; c < tamColunasFacil; c++) {
			jogoFacil[l][c].vizinhos = quantBombasVizinhasFacil(l, c);
		}
	}
}

// procedimento para imprimir o jogo
void imprimirFacil() {
	
	printf("\n\n\t   ");
	for (c = 0; c < tamColunasFacil; c++)
		printf(" %d ", c);
	printf("\n\t  -------------------------------\n");
	for(l = 0; l < tamLinhasFacil; l++) {
		printf("\t%d |", l);
		for(c = 0; c < tamColunasFacil; c++) {
			if(jogoFacil[l][c].foiAberta) {
				if(jogoFacil[l][c].eBomba)
					printf(" * ");
				else
					printf(" %d", jogoFacil[l][c].vizinhos);
			}
			else 
				printf("  ");
			printf("|");
		}
		printf("\n\t  -------------------------------\n");
	}
}

//procedimento para abrir a coordenada escrita
void abrirCelula(int l, int c){
	if(coordenadaValidaFacil(l, c) == 1 && jogoFacil[l][c].foiAberta == 0){
		jogoFacil[l][c].foiAberta = 1;
		if(jogoFacil[l][c].vizinhos == 0) {
			
			abrirCelula(l - 1, c);
			abrirCelula(l + 1, c);
			abrirCelula(l, c - 1);
			abrirCelula(l, c + 1);
			abrirCelula(l - 1, c - 1);
			abrirCelula(l - 1, c + 1);
			abrirCelula(l + 1, c - 1);
			abrirCelula(l + 1, c + 1);
		}
		
	}
}

// função para verificar se ganhou retorna 1 se perder retorna 0
int vitoriaFacil(){
	int quantidade = 0;
	
	for(l = 0; l < tamLinhasFacil; l++) {
		for(c = 0; c < tamColunasFacil; c++) {
			if(jogoFacil[l][c].foiAberta == 0 && jogoFacil[l][c].eBomba == 0) {
				quantidade++;
			}
		}
	}
	return quantidade;
}

//procedimento que lê as coordenadas
void lerCoordsFacil(){
	int linha, coluna;
	
	do {
		imprimirFacil();
		do {
			printf("Digite as coordenadas da linha e coluna: ");
			scanf("%d%d", &linha, &coluna);
			
			if(coordenadaValidaFacil(linha, coluna) == 0) {
				printf("\nCoordenada Invalida");
			}
		}while(coordenadaValidaFacil(linha, coluna) == 0 || jogoFacil[linha][coluna].foiAberta == 1);
	
		abrirCelula(linha, coluna);
	}while(vitoriaFacil() != 0 && jogoFacil[linha][coluna].eBomba == 0);
	
	if(jogoFacil[linha][coluna].eBomba == 1){
		printf("\n\t Voce Perdeu");
	} else {
		printf("\n\t Parabens, acabou de ganhar no modo facil");
	}
}
