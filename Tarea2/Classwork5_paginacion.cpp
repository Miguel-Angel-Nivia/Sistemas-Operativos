#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Estructura para representar una pagina de memoria
struct Pagina {
  int id;
  int posicion;
  bool libre;
};

// Estructura para representar un proceso
struct Proceso {
  int id;
  int tamano;
  int paginaAsignada;
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
      memoriaPaginada[i].posicion = i + 1;
      memoriaPaginada[i].libre = true;
    }
  }

  // Funcion para asignar espacio a un proceso
  bool asignarMemoria(int procesoID, int tamano) {

    int bandera = 0;
    int lugar_proceso = 0;

    for (int i = 0; i < procesos.size(); i++) {
      if (procesoID == procesos[i].id) {
        bandera = 1;
        lugar_proceso = i;
      }
    }

    if (bandera == 1) {

      for (int i = 0; i < memoriaPaginada.size(); i++) {
        if (memoriaPaginada[i].posicion >
            memoriaPaginada[procesos[lugar_proceso].paginaAsignada].posicion) {

          memoriaPaginada[i].posicion = memoriaPaginada[i].posicion - 1;
        }
      }

      memoriaPaginada[procesos[lugar_proceso].paginaAsignada].posicion =
          memoriaPaginada.size();
    } else {
      Proceso nuevoProceso;

      int contador = 0;

      for (int i = 0; i < memoriaPaginada.size(); i++) {
        if (memoriaPaginada[i].libre) {
          contador++;
        }
      }

      if (contador > 0) {

        int bandera = 0;

        for (int i = 0; i < memoriaPaginada.size(); i++) {
          if (memoriaPaginada[i].libre && tamanoPagina >= tamano &&
              bandera == 0) {
            memoriaPaginada[i].libre = false;
            bandera = 1;
            nuevoProceso.id = procesoID;
            nuevoProceso.tamano = tamano;
            nuevoProceso.paginaAsignada = i;
            procesos.push_back(nuevoProceso);
          }
        }
      } else {

        if (tamanoPagina >= tamano) {

          for (int i = 0; i < memoriaPaginada.size(); i++) {
            memoriaPaginada[i].posicion = memoriaPaginada[i].posicion - 1;
          }

          for (int i = 0; i < procesos.size(); i++) {
            if (memoriaPaginada[procesos[i].paginaAsignada].posicion == 0) {
              procesos.erase(procesos.begin() + i);
            }
          }

          for (int i = 0; i < memoriaPaginada.size(); i++) {
            if (memoriaPaginada[i].posicion == 0) {
              memoriaPaginada[i].posicion = memoriaPaginada.size();
              nuevoProceso.id = procesoID;
              nuevoProceso.tamano = tamano;
              nuevoProceso.paginaAsignada = i;
              procesos.push_back(nuevoProceso);
            }
          }
        }
      }
    }
    return 0;
  }

  // Funcion para liberar espacio ocupado por un proceso

  void liberarMemoria(int procesoID) {
    for (int i = 0; i < procesos.size(); i++) {
      if (procesos[i].id == procesoID) {
        memoriaPaginada[procesos[i].paginaAsignada].libre = true;

        for (int j = 0; j < memoriaPaginada.size(); j++) {
          if (memoriaPaginada[j].posicion >
              memoriaPaginada[procesos[i].paginaAsignada].posicion) {

            memoriaPaginada[j].posicion = memoriaPaginada[j].posicion - 1;
          }
        }

        memoriaPaginada[procesos[i].paginaAsignada].posicion =
            memoriaPaginada.size();
        procesos.erase(procesos.begin() + i);
      }
    }
  }

  // Funcion para imprimir el estado de la memoria paginada
  void imprimirEstadoMemoria() {

    std::cout << "Estado de la memoria paginada:" << std::endl;
    for (int i = 0; i < memoriaPaginada.size(); i++) {
      std::cout << "Memoria ID: " << memoriaPaginada[i].id
                << " Estado: " << memoriaPaginada[i].libre
                << " posicion: " << memoriaPaginada[i].posicion << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Procesos en memoria:" << std::endl;
    for (int i = 0; i < procesos.size(); i++) {
      std::cout << "Proceso ID: " << procesos[i].id
                << ", Tamaño:  " << procesos[i].tamano
                << ", Pagina: " << procesos[i].paginaAsignada << " "
                << std::endl;
      std::cout << std::endl;
    }
  }
};

int main() {
  int tamanoMemoria = 100; // Tamaño de la memoria paginada
  int tamanoPagina = 20;   // Tamaño de cada pagina
  SimuladorPaginacion simulador(tamanoMemoria, tamanoPagina);

  // Asignar espacio a procesos
  simulador.asignarMemoria(1, 20);
  simulador.asignarMemoria(2, 20);
  simulador.asignarMemoria(3, 15);
  simulador.asignarMemoria(4, 21);

  simulador.imprimirEstadoMemoria();

  simulador.asignarMemoria(5, 9);
  simulador.asignarMemoria(5, 9);
  simulador.asignarMemoria(6, 9);
  simulador.asignarMemoria(7, 9);

  simulador.imprimirEstadoMemoria();

  // Liberar espacio de procesos
  simulador.liberarMemoria(7);

  // Imprimir estado de la memoria
  simulador.imprimirEstadoMemoria();

  return 0;
}
