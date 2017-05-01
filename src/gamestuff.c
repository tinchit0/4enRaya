#include <stdio.h>
#include "gamestuff.h"

void ImprimirTablero(char partida[N][N]){
	int i; int j;

	printf("  ");for(i=0;i<N;i++) printf("%d   ",i+1);printf("\n");
	printf("  ");for(i=0;i<N;i++) printf("v   ");printf("\n");

	for(i=0;i<N;i++){
		printf(" ");for(j=0;j<N;j++) printf("--- ");printf("\n");
		printf("|");for(j=0;j<N;j++) printf(" %c |",partida[i][j]);printf("\n");
	}

	printf(" ");for(i=0;i<N;i++) printf("--- ");printf("\n");
}

int Posibilidades(char partida[N][N]){
	int j;
	int cont = 0;

	for(j=0;j<N;j++){
		if(partida[0][j] == ' '){
			cont += 1;
		}
	}

	return cont;
}

int VictoriaCPU(char partida[N][N]){
	int i; int j;
    char ficha = FICHA_CPU;
	// Chequeo horizontal
	for(i=0;i<N;i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i][j+1] == ficha){
					if(partida[i][j+2] == ficha){
						if(partida[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(j=0;j<N;j++){
		for(i=0;i<(N-3);i++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j] == ficha){
					if(partida[i+2][j] == ficha){
						if(partida[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(i=0;i<(N-3);i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j+1] == ficha){
					if(partida[i+2][j+2] == ficha){
						if(partida[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal contraria
	for(i=0;i<5;i++){
		for(j=N-1;j>2;j--){
			if(partida[i][j] == ficha){
				if(partida[i+1][j-1] == ficha){
					if(partida[i+2][j-2] == ficha){
						if(partida[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

int VictoriaJugador(char partida[N][N]){
	int i; int j;
    char ficha = FICHA_JUGADOR;
	// Chequeo horizontal
	for(i=0;i<N;i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i][j+1] == ficha){
					if(partida[i][j+2] == ficha){
						if(partida[i][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo vertical
	for(j=0;j<N;j++){
		for(i=0;i<(N-3);i++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j] == ficha){
					if(partida[i+2][j] == ficha){
						if(partida[i+3][j] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal principal
	for(i=0;i<(N-3);i++){
		for(j=0;j<(N-3);j++){
			if(partida[i][j] == ficha){
				if(partida[i+1][j+1] == ficha){
					if(partida[i+2][j+2] == ficha){
						if(partida[i+3][j+3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	// Chequeo diagonal contraria
	for(i=0;i<5;i++){
		for(j=N-1;j>2;j--){
			if(partida[i][j] == ficha){
				if(partida[i+1][j-1] == ficha){
					if(partida[i+2][j-2] == ficha){
						if(partida[i+3][j-3] == ficha){
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

void AplicarTirada(char partida[N][N],int columna, char ficha){
	int i;
	for(i=0;i<N;i++){
		if(partida[N-1-i][columna]==' '){
			partida[N-1-i][columna] = ficha;
			break;
		}
	}
}

double Heuristica(char partida[N][N]){
	if (VictoriaCPU(partida)) return VALOR_VICTORIA;
	if (VictoriaJugador(partida)) return -VALOR_VICTORIA;
	else return 0;
}