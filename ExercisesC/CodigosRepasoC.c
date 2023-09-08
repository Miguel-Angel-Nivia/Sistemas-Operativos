/*
Archivo practica C - Sistemas Operativos
By Miguel Angel Nivia Ortega
*/

#include <stdio.h>

int division(){
   int x, y;
   printf( "Digite la cantidad de estudiantes y en cuantos los quiere dividir: " );
   scanf( "%d%d", &x, &y );
   printf( "Division: %f\n", float( x / y ) );
   return 0;
}

int primo(int x){
    if (x == 0 || x == 1){
        return 0;
    }
    for (int i = 2; i <= x / 2; i++){
        if (x % i == 0) {
        	printf( "%d Es primo", x );
            //return 0;
        }
    }
    printf( "%d No es primo", x );
    return 1;
}

int bisiesto(int ano){
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        printf("%d es un ano bisiesto.\n", ano);
    } 
	else{
        printf("%d no es un ano bisiesto.\n", ano);
    }

    return 0;
}

int factorial(int x){
    if (x == 0 || x == 1){
        return 1;
    } 
	else{
        return x * factorial(x - 1);
    }
}

int potencia(int n, int exp){
    if (exp == 0){
        return 1;
    } 
	else{
        return n * potencia(n, exp - 1);
    } 
    return 0;
}

void parimpar(int x){
	if (x % 2 == 0){
        printf("%d es un numero par.\n", x);
    } 
	else{
        printf("%d es un numero impar.\n", x);
    }
}

int fibonacci(int x, int flag){
	int f = 0, s = 1, prox;
	if (flag == 1){
		if(x < 2){
			return x;
		}
		else{
			return fibonacci(x - 1, 1) + fibonacci(x - 2, 1);
		}
	}
	else{
    	printf("Serie fibonacci: %d, %d, ", f, s);
    	for (int i = 2; i < x; i++){
        	prox = f + s;
        	printf("%d, ", prox);
        	f = s;
        	s = prox;
    	}
	}
	return 0;
}

int esMayuscula(char letra){
	// letras = ['A', 'B', 'C', 'D', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'Ñ', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
    if (letra == 'A' || letra == 'B' || 
		letra == 'C' || letra == 'D' || 
		letra == 'F' || letra == 'G' || 
		letra == 'H' || letra == 'I' || 
		letra == 'J' || letra == 'K' || 
		letra == 'L' || letra == 'M' || 
		letra == 'N' || letra == 'Ñ' || 
		letra == 'O' || letra == 'P' || 
		letra == 'Q' || letra == 'R' || 
		letra == 'S' || letra == 'T' || 
		letra == 'U' || letra == 'V' || 
		letra == 'W' || letra == 'X' || 
		letra == 'Y' || letra == 'Z'){
        printf("%c es una letra mayuscula.\n", letra);
    } 
	else{
        printf("%c es una letra minuscula.\n", letra);
    }
    return 0;
}

int esMinuscula(char letra){
	esMayuscula(letra);
	return 0;
}

int numeroMax(int x, int y, int z){
	int reg;
	if(x > y){
		reg = x;
	}
	else{
		reg = y;
	}
	if(z > reg){
		reg = z;
	}
	printf("El numero mas grande de los numeros %d, %d y %d es = %d", x, y, z, reg );
	return 0;
}

int conversion(int x, int caso){
	if(caso == 1){
		float y = x;
		printf("%f", y);
	}
	else{
		float y = (float)x;
		printf("%f", y);
	}
	return 0;
}

int decOctHex(int n){
    printf("Decimal\t\tOctal\t\tHexadecimal\n");
    for(int i = 1; i <= n; i++){
        printf("%d\t\t%o\t\t%X\n", i, i, i);
    }
    return 0;
}

int main() {
    // division();
    // primo(2);
    // bisiesto(2000);
    // printf("%d", factorial(3));
    // printf("%d", potencia(5, 2));
    // parimpar(10);
    // printf("%d", fibonacci(3, 1));
    // fibonacci(10, 0);
    // esMayuscula('Z');
    // esMinuscula('h');
    // numeroMax(4, 2, 6);
    // conversion(2, 1);
    decOctHex(15);
    return 0;
}


