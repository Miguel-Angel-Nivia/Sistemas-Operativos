#include <iostream>

// funcion para obtener la direccion del stack
void direccion(){
  // soy una variable en el stack
  int stackVar;
  std::cout << "Direccion del stack: " << &stackVar << std::endl;
}

int main(){
  // Llama la funcion para obtener la direccion del stack
  direccion();

  int* heapMem = new int;
  std::cout << "Direccion de la memoria asignada: " << heapMem << std::endl;

  // Obtener la direccion de una funcion en el text/code
  std::cout << "Direccion de la funcion main: " << (void*)main << std::endl;

  delete heapmem;
  return 0;
}
