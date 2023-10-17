// Simulador de Segmentacion

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Estructura para representar un segmento de memoria
struct Segmento{
  int id;
  int tamano;
  bool libre;
};

// Estructura para representar un proceso

struct Proceso {
  int id;
  int tamano;
  int segmentoAsignado;
};

class SimuladorSegmentacion{

private:
  int tamanoMemoria;
  std::vector<Segmento> memoriaSegmentada;
  std::vector<Proceso> procesos;

public:
//Construtor, inicializa el tamaño de la memoria y el vector de segmentos, si uniforme es true se creara segmentacion uniforme con el tamano del primer valor del vector segmentos, de lo contrario se creara segmentacion con los tamanos del vector segmentos.
  SimuladorSegmentacion(int tamano,std::vector<int> segmentos, bool uniforme) : tamanoMemoria(tamano){
    if (uniforme) {
      int tamano = segmentos[0];
      int numSegmentos = tamanoMemoria/tamano;
      memoriaSegmentada.resize(numSegmentos);
        for(int i=0; i<numSegmentos; i++){
          memoriaSegmentada[i].id = i;
          memoriaSegmentada[i].tamano = tamano;
          memoriaSegmentada[i].libre = true;
      }
    }else{
      int sum = 0;
      bool comTamano = true; 
      for(int i = 0; i< segmentos.size() and comTamano;i++){
        sum = sum + segmentos[i];
        if (sum > tamanoMemoria){
          comTamano = false;
        }    
      }
      if (comTamano){
        memoriaSegmentada.resize(segmentos.size());
        for(int i = 0; i<segmentos.size();i++){
          memoriaSegmentada[i].id = i;
          memoriaSegmentada[i].tamano = segmentos[i];
          memoriaSegmentada[i].libre = true;
        }
      }else{
        std::cout << "No se puede crear la memoria segmentada" << std::endl;
      }
    }
    
}
  bool asignarMemoria(int procesoID, int tamano){
    bool flag = false;
    int i = 0;
    while (i<memoriaSegmentada.size() && !flag){
      if(memoriaSegmentada[i].libre && memoriaSegmentada[i].tamano >= tamano){
        memoriaSegmentada[i].libre = false;
        Proceso nuevoProceso;
        nuevoProceso.id = procesoID;
        nuevoProceso.tamano = tamano;
        nuevoProceso.segmentoAsignado = i;
        procesos.push_back(nuevoProceso);
        flag = true;
      }
      i=i+1;
    }
    return flag;
  }

void liberarMemoria(int procesoID){
  bool flag = false;
  for (int i=0; i<procesos.size() && flag == false; i++){
    if (procesos[i].id == procesoID){
      memoriaSegmentada[procesos[i].segmentoAsignado].libre = true;
      flag = true;
      procesos.erase(procesos.begin() + i);
    }
  }
}

void imprimirMemoria(){
  std::cout << "Estado de la memoria Segmentada:" << std::endl;
  for (int i = 0; i < memoriaSegmentada.size(); i++){
    std::cout << "Segmento " << memoriaSegmentada[i].id << " Estado: " << (memoriaSegmentada[i].libre == 0 ? "Ocupado":"Libre") << " Capacida: " << memoriaSegmentada[i].tamano << std::endl;
  }
  std::cout << "Procesos en memoria:"<< std::endl;
  for (int i = 0; i < procesos.size(); i++){
    std::cout << "Proceso ID: " << procesos[i].id << " - Tamaño: " << procesos[i].tamano << " - Segmento Asignado: " << procesos[i].segmentoAsignado << std::endl;
  }
}
};

int main(){

  int tamanoMemoria = 100; // Tamaño de la memoria segmentada
  std::vector<int> tamanoSegmento = {20,50,30};   // Tamaño de cada segmento
  bool uniforme = false;
  SimuladorSegmentacion simulador(tamanoMemoria, tamanoSegmento, uniforme);

  // Asignar memoria para procesos
  simulador.asignarMemoria(1,30);
  simulador.asignarMemoria(2,4);
  simulador.asignarMemoria(3,15);

  simulador.imprimirMemoria();
  //liberar espacio de procesos
  simulador.liberarMemoria(2);

  simulador.asignarMemoria(6,10);

  simulador.imprimirMemoria();

  return 0;
  //TODO: realizar la simulacion de asignacion y liberacion de memoria aqui.

  //TODO: imprimir el estado de la memoria paginada.
}
