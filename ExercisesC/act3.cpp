#include <iostream>

int main(){
  const int tamanoArray = 5;
  int numeros[tamanoArray] = {10, 20, 30, 40, 50}; // Declaración de un array de enteros

  // imprimir el contenido del array
  std::cout << "Contenido del array 'numeros': ";
  for (int i = 0; i < tamanoArray; i++) {
    std::cout << numeros[i] << " ";
  }
  std::cout << std::endl;

  // Declarar un puntero que apunta al inicio del array
  int* punteroNumeros = numeros;

  // Utilizar el puntero para acceder y modificar elementos del array
  punteroNumeros[1] = 99; // Modificar el segundo elemento del array
  
  // imprimir el contenido del array después de la modificación
  std::cout << "Contenido del array 'numeros' después de la modificación: ";
  for (int i; i < tamanoArray; i++) {
    std::cout << numeros[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
