#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "gamestuff.h"
#include "minimaxvar.h"
#include "highscores.h"

// Funciones de desarrollo del juego
void EsperarENTER();
void NuevaPartida(char [N][N]);
int JuegaJugador(char [N][N],int ,char );
int JuegaCPU(char [N][N],int ,char);
void PantallaPrincipal();
void PantallaSeleccionDificultad(int *);
void PantallaRecords();
void Partida1jug();
void Partida2jug();

int main(){
	PantallaPrincipal();
	system("cls");
}

void EsperarENTER(){
	char r = getch();
	while (r != 13){
		Beep(250,400);
		r = getch();
	}
}

void NuevaPartida(char partida[N][N]){
	int i; int j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			partida[i][j] = ' ';
		}
	}
}

int JuegaJugador(char partida[N][N],int numero_jugador,char ficha){
	char respuesta;
	int columna;

	system("cls");
	ImprimirTablero(partida);
	printf("(Presione ESC para volver al menu inicial)\n");
	if (numero_jugador == 0){
		printf("Turno jugador: ");
	}
	else{
		printf("Turno jugador %d: ",numero_jugador);
	}
	respuesta = getche();
	if(respuesta == 27) return 1; // Parametro de salida
	columna = respuesta-'0'-1;
	if(columna <0 || columna>7){
		system("cls");
		ImprimirTablero(partida);
		printf("\a");
		printf("Que columna es esa? Selecciona otra. (Presione ENTER para continuar)\n");
		EsperarENTER();
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	if(partida[0][columna] != ' '){
		system("cls");
		ImprimirTablero(partida);
		printf("\a");
		printf("La columna %d esta llena! Selecciona otra. (Presione ENTER para continuar)\n",columna+1);
		EsperarENTER();
		return JuegaJugador(partida,numero_jugador,ficha);
	}
	AplicarTirada(partida,columna,ficha);
	return 0;
}

int JuegaCPU(char partida[N][N], int dificultad,char ficha){
	system("cls");
	ImprimirTablero(partida);
	//printf("Valor heuristico del tablero actual: %lf\n",Heuristica(partida));
	printf("El rival esta pensando...\n");

	int columna = ElegirTirada(partida,dificultad);
	AplicarTirada(partida,columna,ficha);
	//system("PAUSE");
	return 0;
}

void PantallaPrincipal(){
	system("cls");
	printf("\n\n\n\n");
	printf("                                                            \n");
	printf("            #             #####                             \n");
	printf("           ##             #    #                            \n");
	printf("          # #   ##  ####  #    # #####  #    # #####        \n");
	printf("         #  #  #  # #   # #####       # #    #      #       \n");
	printf("        #   #  #### #   # #  #    ##### ######  #####       \n");
	printf("       ####### #    #   # #   #  #    #      # #    #       \n");
	printf("            #   ### #   # #    # ###### #####  ######       \n");
	printf("                                                            \n");
	printf("              1 - Jugar contra el ordenador                 \n");
	printf("                    2 - Dos jugadores                       \n");
	printf("                                                            \n");
	printf("        Para ver las mejores puntuaciones presiona R        \n");
	printf("                                                            \n");
	printf("             Para salir del juego presiona ESC              \n");

	char Respuesta = getch();
	if (Respuesta == 27){
		return;
	}
	if (Respuesta == 'R'||Respuesta == 'r'){
		PantallaRecords();
		return;
	}
	if (Respuesta == 'E'||Respuesta == 'e'){
		char comillas =  '"';
		system("experts\\4r-experts");
		PantallaPrincipal();
		return;
	}
	if (Respuesta == '1'){
		Partida1jug();
		return;
	}
	if (Respuesta == '2'){
		Partida2jug();
		return;
	}
	else{
		Beep(250,400);
		PantallaPrincipal();
		return;
	}
}

void PantallaSeleccionDificultad(int *dificultad){
	system("cls");
	printf("Seleccione la dificultad:\n");
	printf("    1 - Facil \n");
	printf("    2 - Normal \n");
	printf("    3 - Dificil \n");

	printf("\nTeclea el numero de dificultad que deseas: ");
	char respuesta;
	respuesta = getche();
	*dificultad = respuesta - '0'-1;
	if (*dificultad < 0 || *dificultad > 2){
		printf("\a");
		printf("\n1,2 o 3. No hay mas opciones!!!\n");
		printf("(Presiona ENTER para continuar)");
		EsperarENTER();
		PantallaSeleccionDificultad(dificultad);
	}
}

void PantallaRecords(){
	int i;
	char persona[30][10]; int puntuacion[30];
	LeerRecords(persona,puntuacion);
	system("cls");
	printf("################### HIGHSCORES ###################\n");
	printf("\n     DIFICIL    |     NORMAL     |      FACIL     \n");
	printf("--------------------------------------------------\n");
	for (i=0;i<10;i++){
		printf(" %-10s %3d | %-10s %3d | %-10s %3d\n",persona[i],puntuacion[i],persona[10+i],puntuacion[10+i],persona[20+i],puntuacion[20+i]);
	}
	printf("\n(Presiona cualquier tecla para abandonar esta pantalla)\n");
	getch();
	PantallaPrincipal();
}

void Partida1jug(){
	char partida[N][N]; int DIFICULTAD;
	NuevaPartida(partida);
	PantallaSeleccionDificultad(&DIFICULTAD);

	char persona[30][10]; int puntuacion[30];
	LeerRecords(persona,puntuacion);
	int MIN_RECORD = puntuacion[(3-DIFICULTAD)*10-1];

	int contador_jugadas = 1;
	while(1){
		// Turno Jugador
		int EXIT = JuegaJugador(partida,0,'O');
		if(EXIT == 1){
			PantallaPrincipal();
			break;
		}
		if(VictoriaJugador(partida)){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el jugador en %d jugadas! ",contador_jugadas);
			if (contador_jugadas< MIN_RECORD){
				NuevoRecord(contador_jugadas,DIFICULTAD);
				PantallaRecords();
			}
			else{
				printf("(Presione ENTER para continuar)");
				EsperarENTER();
				PantallaPrincipal();
			}
			break;
		}
		// Turno CPU
		JuegaCPU(partida,DIFICULTAD,'X');
		if(VictoriaCPU(partida)){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el CPU! (Presione ENTER para continuar)");
			EsperarENTER();
			PantallaPrincipal();
			break;
		}

		// Si se llena el tablero
		if(Posibilidades(partida)==0){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Se acabo el juego. Empate. (Presione ENTER para continuar)");
			EsperarENTER();
			PantallaPrincipal();
			break;
		}

		contador_jugadas++;
	}
}

void Partida2jug(){
	char partida[N][N]; int EXIT;
	NuevaPartida(partida);

	int contador_jugadas = 1;
	while(1){
		// Turno Jugador 1
		EXIT = JuegaJugador(partida,1,'O');
		if(EXIT == 1){
			PantallaPrincipal();
			break;
		}
		if(VictoriaJugador(partida)){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el jugador 1 en %d jugadas! (Presione ENTER para continuar)",contador_jugadas);
			EsperarENTER();
			PantallaPrincipal();
			break;
		}
		// Turno CPU
		EXIT = JuegaJugador(partida,2,'X');
		if(EXIT == 1){
			PantallaPrincipal();
			break;
		}
		if(VictoriaCPU(partida)){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Gana el jugador 2 en %d jugadas! (Presione ENTER para continuar)",contador_jugadas);
			EsperarENTER();
			PantallaPrincipal();
			break;
		}

		// Si se llena el tablero
		if(Posibilidades(partida)==0){
			system("cls");
			ImprimirTablero(partida);
			printf("\a");
			printf("Se acabo el juego. Empate. (Presione ENTER para continuar)");
			EsperarENTER();
			PantallaPrincipal();
			break;
		}

		contador_jugadas++;
	}
}