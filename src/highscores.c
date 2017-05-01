#include <stdio.h>
#include "highscores.h"

void CopiarNombre(char *dest, char *source){ // Idem strcpy
	int i=0;
	while (source[i]!='\0'){
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

void LeerRecords(char persona[30][10],int puntuacion[30]){
	int i;
	FILE *HIGHSCORES = fopen("highscores.txt","r+");
	for (i=0;i<30;i++) fscanf(HIGHSCORES,"%s %d",persona[i],puntuacion+i);
	fclose(HIGHSCORES);
}

void NuevoRecord(int puntuacion_jugador,int dificultad){
	printf("\n\n********************* NUEVO RECORD!!! *********************\n");

	/* Leer los records actuales */
	char persona[30][10]; int puntuacion[30];
	LeerRecords(persona,puntuacion);

	/* Ubicar que posicion ha alcanzado */
	int pos=(3-dificultad)*10-1;
	while(puntuacion_jugador<puntuacion[pos]){
		pos--;
	}
	printf("\nEnhorabuena! Estas en el puesto %d de este nivel\n",pos%10+2);

	/* Registro del record */
	char nombre_jugador[10];
	printf("Introduce tu nombre (maximo 10 caracteres): "); scanf("%s",&nombre_jugador);
	int i;
	for (i=(3-dificultad)*10-1;i>(3-dificultad-1)*10;i--){
		if (puntuacion_jugador < puntuacion[i-1]){
			CopiarNombre(persona[i],persona[i-1]);
			puntuacion[i] = puntuacion[i-1];
			CopiarNombre(persona[i-1],nombre_jugador);
			puntuacion[i-1] = puntuacion_jugador;
		}
		else break;
	}

	/* Reescribir el archivo de records */
	FILE *NEWHIGHSCORES = fopen("highscores.txt","w+");
	for (i=0;i<30;i++){
		fprintf(NEWHIGHSCORES,"%s %d\n",persona[i],puntuacion[i]);
	}
	fclose(NEWHIGHSCORES);
}