// Simulador de Paginacion

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Estructura para representar una pagina de memoria
struct Pagina {
  int id;
  bool libre;
};

// Estructura para representar un proceso

struct Proceso {
  int id;
  int tamano;
  std::vector<int> paginasAsignadas;
};

class SimuladorPaginacion {

private:
  int tamanoMemoria;
  int tamanoPagina;
  std::vector<Pagina> memoriaPaginada;
  std::vector<Proceso> procesos;

public:
  SimuladorPaginacion(int tamano, int tamanoPag)
      : tamanoMemoria(tamano), tamanoPagina(tamanoPag) {
    int numPaginas = tamanoMemoria / tamanoPagina;
    memoriaPaginada.resize(numPaginas);
    for (int i = 0; i < numPaginas; i++) {
      memoriaPaginada[i].id = i;
      memoriaPaginada[i].libre = true;
    }
  }

  // Funcion para asignar espacio a un proceso
  bool asignarMemoria(int procesoID, int tamano) {

    int numPaginasNecesarias = (tamano + tamanoPagina - 1) / tamanoPagina;
    std::vector<int> paginasAsignadas;

    for (int i = 0; i < memoriaPaginada.size(); i++) {
      if (memoriaPaginada[i].libre && numPaginasNecesarias > 0) {
        paginasAsignadas.push_back(i);
        numPaginasNecesarias--;
      }
    }

    if (numPaginasNecesarias == 0) {
      Proceso nuevoProceso;
      nuevoProceso.id = procesoID;
      nuevoProceso.tamano = tamano;
      nuevoProceso.paginasAsignadas = paginasAsignadas;
      procesos.push_back(nuevoProceso);
      for (int i = 0; i < paginasAsignadas.size(); i++) {
        memoriaPaginada[paginasAsignadas[i]].libre = false;
      }
    } else {
      return false;
    } // No se pudo asignar memoria
  }

  // Funcion para liberar espacio ocupado por un proceso

  void liberarMemoria(int procesoID) {
    for (int i = 0; i < procesos.size(); i++) {
      if (procesos[i].id == procesoID) {
        for (int j = 0; j < procesos[i].paginasAsignadas.size(); j++) {
          memoriaPaginada[procesos[i].paginasAsignadas[j]].libre = true;
        }
        procesos.erase(procesos.begin() + i);
      }
    }
  }

  // Funcion para imprimir el estado de la memoria paginada
  void imprimirEstadoMemoria() {

    std::cout << "Estado de la memoria paginada:" << std::endl;
    for (int i = 0; i < memoriaPaginada.size(); i++) {
    }
    std::cout << std::endl;

    std::cout << "Procesos en memoria:" << std::endl;
    for (const Proceso &p : procesos) {
      std::cout << "Proceso ID" << p.id << ", Tamaño:  " << p.tamano
                << ", Paginas: ";
      for (int pagina : p.paginasAsignadas) {
        std::cout << pagina << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  int tamanoMemoria = 100; // Tamaño de la memoria paginada
  int tamanoPagina = 20;   // Tamaño de cada pagina
  SimuladorPaginacion simulador(tamanoMemoria, tamanoPagina);

  // Asignar espacio a procesos
  simulador.asignarMemoria(1, 30);
  simulador.asignarMemoria(2, 40);
  simulador.asignarMemoria(3, 15);

  // Liberar espacio de procesos
  simulador.liberarMemoria(1);

  // Imprimir estado de la memoria
  simulador.imprimirEstadoMemoria();

  return 0;
}
