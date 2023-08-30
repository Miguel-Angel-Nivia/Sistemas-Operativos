/*
 * @name:
 * Tarea #1
 * @version:
 * Embarcadero Dev-C++ 6.3
 * @author and owners:
 * Daniel Vasquez (8963154)
 * Wilian Chapid Tobar (8965113)
 * Miguel Angel Nivia Ortega (8958691)
 * @description:
 * Intrucciones del modelo del ciclo basico de instrucciones..
 */

// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defines
#define CAPACIDAD 500

// Variables globales
int flag = 0;
extern int flag;


// cambio de las cadenas de puntero a cadenas fijas para no enredarnos con asignacion de memoria
char unidadControl[40];
int acumulador = 0;
int PC = 200;
char ICR[40];
int MAR = 0;
int MDR = 0;

int memoria[CAPACIDAD];
extern int memoria[CAPACIDAD];

// Codigo

typedef enum { SET, LDR, ADD, SUB, INC, DEC, STR, SHW, PAUSE, END } Instruction;

Instruction decodeInstruction(const char *instruction_str) {
  	Instruction instruccion;
  	if (strcmp(instruction_str, "SET") == 0)
    	instruccion = SET;
  	else if (strcmp(instruction_str, "LDR") == 0)
    	instruccion = LDR;
  	else if (strcmp(instruction_str, "ADD") == 0)
    	instruccion = ADD;
    else if (strcmp(instruction_str, "SUB") == 0)
    	instruccion = SUB;
  	else if (strcmp(instruction_str, "INC") == 0)
    	instruccion = INC;
  	else if (strcmp(instruction_str, "DEC") == 0)
    	instruccion = DEC;
  	else if (strcmp(instruction_str, "STR") == 0)
    	instruccion = STR;
  	else if (strcmp(instruction_str, "SHW") == 0)
    	instruccion = SHW;
  	else if (strcmp(instruction_str, "PAUSE") == 0)
    	instruccion = PAUSE;
  	else if (strcmp(instruction_str, "END") == 0)
    	instruccion = END;
  	return instruccion;
}

int Creacionmemoria() {
  	for (int i = 1; i <= CAPACIDAD; i++) {
    	memoria[i] = 0;
  	}
  	return 0;
}

int impresionMemoria(int *memoria) {
  	printf("\n");
  	for (int i = 1; i <= CAPACIDAD; i++) {
    	printf("%d ", memoria[i]);
  	}
  	printf("\n");
  	return 0;
}

int cambios() {
  	printf("\nUnidad De Control: %s\n", unidadControl);
  	printf("Acumulador: %d\n", acumulador);
  	printf("PC: %d\n", PC);
  	printf("ICR: %s\n", ICR);
  	printf("MAR: %d\n", MAR);
  	printf("MDR: %d\n\n", MDR);
  	return 0;
}

void concatenate(const char *instruccion, const char *var1){
	unidadControl[0] = '\0';
	ICR[0] = '\0';
	strcpy(unidadControl, instruccion);
	strcat(unidadControl, var1);
	strcpy(ICR, unidadControl);
}

// En las instrucciones solo hay que borrar las lineas aqui mencionadas y dejar en cada instruccion el acumulador que se cambia solo
void updateState(const char *instruccion, const char *ubi){
	int pos = atoi(ubi + 1);
  	PC++;
  	concatenate(instruccion, ubi);
  	MDR = memoria[pos];
  	MAR = pos;
}

// instrucciones

void set(const char *ubi, int var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	// Agregar a memoria
  	memoria[pos] = var1;
  	impresionMemoria(memoria);
  	cambios();
}


void ldr(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	// Actualizamos el acumulador
  	acumulador = memoria[pos];
  	cambios();
}

void add(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	if (strstr(var1, "NULL") && strstr(var2, "NULL")) {
    	acumulador += memoria[pos];
    	MDR = memoria[pos];
  		MAR = pos;
  	} else if ((strcmp(var1, "NULL") != 0) && strstr(var2, "NULL")) {
    	int pos2 = atoi(var1 + 1);
    	acumulador = memoria[pos];
    	acumulador += memoria[pos2];
    	MDR = memoria[pos2];
  		MAR = pos2;
  	} else if ((strcmp(var1, "NULL") != 0) && (strcmp(var2, "NULL") != 0)) {
    	int pos2 = atoi(var1 + 1);
    	int pos3 = atoi(var2 + 1);
    	acumulador = memoria[pos];
    	acumulador += memoria[pos2];
    	memoria[pos3] = acumulador;
    	MDR = memoria[pos3];
  		MAR = pos3;
  	}
  	impresionMemoria(memoria);
  	cambios();
}

void sub(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	if (strstr(var1, "NULL") && strstr(var2, "NULL")) {
    	acumulador -= memoria[pos];
    	MDR = memoria[pos];
  		MAR = pos;
  	} else if ((strcmp(var1, "NULL") != 0) && strstr(var2, "NULL")) {
    	int pos2 = atoi(var1 + 1);
    	acumulador = memoria[pos];
    	acumulador -= memoria[pos2];
    	MDR = memoria[pos2];
  		MAR = pos2;
  	} else if ((strcmp(var1, "NULL") != 0) && (strcmp(var2, "NULL") != 0)) {
    	int pos2 = atoi(var1 + 1);
    	int pos3 = atoi(var2 + 1);
    	acumulador = memoria[pos];
    	acumulador -= memoria[pos2];
    	memoria[pos3] = acumulador;
    	MDR = memoria[pos3];
  		MAR = pos3;
  	}
  	impresionMemoria(memoria);
  	cambios();
}

void inc(const char *ubi, const char *var1, const char *var2, const char *var3) {
	int pos = atoi(ubi + 1);
	memoria[pos]++;
	// acumulador = memoria[pos];
	impresionMemoria(memoria);
	cambios();
}

void dec(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	memoria[pos]--;
  	// acumulador = memoria[pos];
  	impresionMemoria(memoria);
  	cambios();
}

void str(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	if (pos<sizeof(memoria)){
  		memoria[pos] = acumulador;
  	} else{
  		printf("Invalid Address\n");
  	}
  	impresionMemoria(memoria);
  	cambios();
}

void shw(const char *ubi, const char *var1, const char *var2, const char *var3) {
  	int pos = atoi(ubi + 1);
  	if (strstr(ubi, "ACC") && flag == 1) {
    	printf("Acumulador: %d\n", acumulador);
  	} else if (strstr(ubi, "ICR") && flag == 1) {
    	printf("ICR: %s\n", ICR);
  	} else if (ubi == "MAR" && flag == 1) {
    	printf("MAR: %d\n", MAR);
  	} else if (strstr(ubi, "MDR") && flag == 1) {
    	printf("MDR: %d\n", MDR);
  	} else if (strstr(ubi, "UC") && flag == 1) {
    	printf("Unidad De Control: %s\n", unidadControl);
  	} else if (ubi[0] == 'D') {
    	printf("Posicion %s: %d\n", ubi, memoria[pos]);
  	} else {
    	printf("Error, no puedes visualizar esto acá\n");
  	}
}

void pse() {
	if (flag == 0){
  		flag = 1;
  	} else if( flag == 1){
  		flag = 0;
  	}
}
