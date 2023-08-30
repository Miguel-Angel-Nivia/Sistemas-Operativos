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
 * Modelo basico de un lector de programa assembler con instrucciones y
 * ejecuciones.
 */

// imports

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instrucciones.h"

// Codigo

void executeInstruction(Instruction instruction, const char *var1, const char *var2, const char *var3,  const char *var4) {
    switch (instruction) {
      	case SET:
        	printf("set\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	set(var1, atoi(var2), var3, var4);
        	updateState("SET ", var1);
        	break;
      	case LDR:
        	printf("ldr\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	ldr(var1, var2, var3, var4);
        	updateState("LDR ", var1);
        	break;
      	case ADD:
        	printf("add\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	add(var1, var2, var3, var4);
        	PC++;
  			concatenate("ADD ", var1);
        	break;
    	case SUB:
    		printf("sub\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	sub(var1, var2, var3, var4);
        	PC++;
  			concatenate("SUB ", var1);
        	break;
      	case INC:
        	printf("inc\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	inc(var1, var2, var3, var4);
        	updateState("INC ", var1);
        	break;
      	case DEC:
        	printf("dec\n");
       		printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	dec(var1, var2, var3, var4);
        	updateState("DEC ", var1);
        	break;
      	case STR:
        	printf("str\n");
        	printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	str(var1, var2, var3, var4);
        	updateState("STR ", var1);
        	break;
      	case SHW:
        	printf("shw\n");
       		printf("%d, %s, %s, %s, %s\n", instruction, var1, var2, var3, var4);
        	shw(var1, var2, var3, var4);
        	PC++;
      		break;
      	case PAUSE:
        	printf("pau\n");
        	pse();
        	PC++;
        	break;
      	case END:
        	printf("10\n");
        	break;
    }
}

int main() {
  // Creacion de la memoria
    Creacionmemoria();
    //impresionMemoria(memoria);
    
    Instruction instruccion_actual;
    char *seccion_cadena;
    char *valores[5];
    
  // lectura Archivo
  	char entrada[9]; 
  	printf("Bienvenido, porfavor ingrese el txt de tu archivo: ");
	scanf("%s", entrada);
  	while (strcmp(entrada, "fin") != 0){
	    FILE *file = fopen(entrada, "r");
	    if (file == NULL) {
	      printf("No se pudo abrir el archivo.\n");
	      return 1;
	    }
	    char line[100];
	    char end_program[] = "END NULL NULL NULL";

	    /*colocar band, variable para ver cuando este en pausa el programa
	    es decir que no se salten las operaciones diferentes a SHW*/
	
	    while (strstr(fgets(line, sizeof(line), file), end_program) == NULL) {
	      //printf("%s", line);
	      int i = 0;
	      seccion_cadena = strtok(line, " ");
	      instruccion_actual = decodeInstruction(seccion_cadena); 
	      seccion_cadena = strtok(NULL, " ");
	      // printf("Token: %d\n", instruccion_actual);
	      while (seccion_cadena != NULL) {
	          valores[i] = strdup(seccion_cadena);
	          // printf("Token: %s\n", valores[i]);
	          seccion_cadena = strtok(NULL, " ");
	          i++;
	      }
	      /*incorporacion bandera para que se ejecute normalmente y cuando este activa
	      solo se debe dejar pasar la instruccion show y pause para volver a leer otras.*/
	      if((flag == 0) || (flag == 1 && (instruccion_actual == SHW || instruccion_actual == PAUSE))){
	        executeInstruction(instruccion_actual, valores[0], valores[1], valores[2], valores[3]);
	      }    
	    }
    fclose(file);
    printf("\n Quiere ingresar otro txt a probar o escriba -fin- para acabar ejecucion: ");
	scanf("%s", entrada);
	}
  return 0;
}