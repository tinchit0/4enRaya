#include <stdio.h>
#include <stdlib.h>
#include "gamestuff.h"
#include "minimaxvar.h"

void CopiaTablero(char tablero1[N][N], char tablero2[N][N]){
	int i; int j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			tablero2[i][j] = tablero1[i][j];
		}
	}
}

Nodo CreaNodo(char tablero[N][N],int nivel,int dificultad){
	int i; int j=0;
	Nodo p;

	p.nivel = nivel;
	CopiaTablero(tablero,p.tablero);
	p.n_hijos = Posibilidades(tablero);
	p.valor = 0;
	if (VictoriaCPU(p.tablero) || VictoriaJugador(p.tablero) || p.nivel == 2*dificultad+2){
        p.n_hijos = 0;
	}

	if (p.n_hijos != 0){
        p.hijos = (Nodo **) malloc(p.n_hijos*sizeof(Nodo *));
        p.movimientos = (int *) malloc(p.n_hijos*sizeof(int));
        for(i=0;i<N;i++){
            if(tablero[0][i] == ' '){
                p.movimientos[j] = i;
                j += 1;
            }
        }
	}
	else{
        p.hijos = NULL;
        p.movimientos = NULL;
	}


	return p;
}

void CreaNivel(Nodo *Padre,char ficha,int dificultad){
	int i;
	Nodo *Hijo;

	for(i=0;i<Padre->n_hijos;i++){
		Hijo = (Nodo *) malloc(sizeof(Nodo));
		CopiaTablero(Padre->tablero,Hijo->tablero);
		AplicarTirada(Hijo->tablero,Padre->movimientos[i],ficha);
		*Hijo = CreaNodo(Hijo->tablero,Padre->nivel+1,dificultad);
		Padre->hijos[i] = Hijo;
	}
}

void CreaDobleNivel(Nodo *raiz,int dificultad){
	int i;
	CreaNivel(raiz,FICHA_CPU,dificultad);
	for(i=0;i<raiz->n_hijos;i++){
		CreaNivel(raiz->hijos[i],FICHA_JUGADOR,dificultad);
	}
}

void CreaArbol(Nodo *raiz, int profundidad, int dificultad){
	CreaDobleNivel(raiz,dificultad);
	if(profundidad == 0) return;
	else{
		int i; int j;
		for(i=0;i<raiz->n_hijos;i++){
			for(j=0;j<raiz->hijos[i]->n_hijos;j++){
				CreaArbol(raiz->hijos[i]->hijos[j],profundidad-1,dificultad);
			}
		}
	}
	return;
}

void BorraArbol(Nodo *raiz){
	if(raiz->n_hijos == 0){
        free(raiz);
	}
	else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            BorraArbol(raiz->hijos[i]);
        }
        free(raiz->hijos);
        free(raiz->movimientos);
	}

	return;
}

void ImprimirArbol(Nodo * raiz){
    char * tab = "";
    if (raiz->nivel != 0){
        tab = (char *) malloc((2*raiz->nivel+1)*sizeof(char));
        int j; for (j=0;j<2*raiz->nivel;j++) tab[j] = ' ';
        tab[2*raiz->nivel] = '\0';
    }
    if (raiz->n_hijos == 0) printf("%sNodo (valor %lf)\n",tab,raiz->valor);
    else{
        int i;
        printf("%sNodo (valor %lf)\n",tab,raiz->valor);
        for (i=0;i<raiz->n_hijos;i++) ImprimirArbol(raiz->hijos[i]);
    }
    free(tab);
}

void ValorarHojas(Nodo *raiz){
    if (raiz->n_hijos == 0){
        raiz->valor = Heuristica(raiz->tablero);
    }
    else{
        int i;
        for (i=0;i<raiz->n_hijos;i++){
            ValorarHojas(raiz->hijos[i]);
        }
    }
}

void MiniMax(Nodo *Raiz){
    int i;
	// Esta es una ligera variante del minimax, donde las herencias se dividen entre 2
	if (Raiz->n_hijos != 0){
        for (i=0;i<Raiz->n_hijos;i++){
            if (Raiz->hijos[i]->n_hijos != 0){
                MiniMax(Raiz->hijos[i]);
            }
        }

        if (Raiz->nivel % 2 == 0){ // MAX
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->n_hijos;i++){
                if (Raiz->hijos[i]->valor > Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
            }
        }

		if (Raiz->nivel % 2 == 1){ // Min
            Raiz->valor = Raiz->hijos[0]->valor;
            for (i=1;i<Raiz->n_hijos;i++){
                if (Raiz->hijos[i]->valor < Raiz->valor){
                    Raiz->valor = Raiz->hijos[i]->valor;
                }
            }
        }

		Raiz->valor /= 2;
	}
}

int ElegirTirada(char partida[N][N], int dificultad){
	Nodo Raiz = CreaNodo(partida,0,dificultad);
	int movimiento;
	CreaArbol(&Raiz,dificultad,dificultad);
	ValorarHojas(&Raiz);
	MiniMax(&Raiz);
	//ImprimirArbol(&Raiz);

	// Elegimos random entre todas las posibilidades que son igual de buenas
	int num_tiradas_buenas = 0;
	int tiradas_buenas[8];
	int i; int j=0;
	for (i=0;i<Raiz.n_hijos;i++){
		if (Raiz.hijos[i]->valor == 2.0*Raiz.valor){
			num_tiradas_buenas++;
			tiradas_buenas[j] = Raiz.movimientos[i];
			j++;
		}
	}
	int index = rand()%num_tiradas_buenas;
	movimiento = tiradas_buenas[index];
	BorraArbol(&Raiz);

	return movimiento;
}