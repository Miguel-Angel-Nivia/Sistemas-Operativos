#include <iostream>

int main(){
  // Declaracion y asignacion de una variable
  int variablel = 42;

  // Presente el valor almacenado en la variable
  std::cout << "Valor almacenado: " << variablel << std::endl;

  // Presente la direccion de memoria
  std::cout << "Direccion de memoria: " << &variablel << std::endl;

  // Puntero que "apunta" a la direccion de variablel
  int * puntero = &variablel;
  *puntero = 219;

  // Presente el valor almacenado en la variable
  std::cout << "Valor almacenado: " << variablel << std::endl;
  
  return 0;
}
