#include <iostream>
using namespace std;

int main(){
  // Declare y asigne una variable
  float una_variable = 999.9;
  
  // Declare y asigne a un puntero la referencia a la anterior variable
  float * un puntero = &una_variable;
  
  // Imprima el valor almacenado en el puntero
  cout << "Puntero: " << *un_puntero << endl;
  
  // Modifique el valor del puntero
  *un_puntero = 1000;
  
  // Imprima el valor almacenado
  cout << "Valor almacenado: " << una_variable << ::endl;
  
  // Cree una referencia
  float &una_referencia = una variable;
  
  // Modifique la referencia
  una_referencia = 1999.9;
  
  // Imprima el valor
  cout << "Valor de referencia: " << una_referencia << endl;
  
  return 0;
}

