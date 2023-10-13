#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// variable Global
int pos = 0;
int cambio = 0;

class Reader {
public:
    // Datos del txt
    int memoria = 0, cant = 0, opcion = 0;
    std::vector<std::string> particiones;
    std::vector<int> particionesInt;
    std::vector<std::string> sol1, sol2, sol3;
    std::vector<int> sol1Int, sol2Int, sol3Int;
	    
    Reader() {
	    std::string entrada;
	    std::cout << "Escriba el archivo de entrada: ";
	    std::cin >> entrada;
	    std::string nombreArchivoEntrada = entrada;
	    std::ifstream archivoEntrada(nombreArchivoEntrada);
	        
	    if (!archivoEntrada.is_open()) {
	        throw std::runtime_error("No se pudo abrir el archivo de entrada.");
	    }
	        
	    std::string linea;
	    while (std::getline(archivoEntrada, linea)) {
		// Comentarios
	        if (linea.empty() || linea[0] == '#') {continue;}
	        // Asignacion de la memoria
	        else if (memoria == 0) {memoria = std::stoi(linea);}
	        // Asignacion de la cantidad de particiones
	        else if (cant == 0) {cant = std::stoi(linea);}
	        // Asignacion de las particiones
	        else if (particiones.empty()) {
			std::istringstream iss(linea);
		        std::string num;
		        while (iss >> num) {
		            particiones.push_back(num);
		        };
		}
	        // Asignacion del Algoritmo elegido
		else if (opcion == 0) {opcion = std::stoi(linea);}
		// Asignacion de las solicitudes (En total 3)
		else if (sol1.empty()) {
	        // Divide la línea en componentes y agrega cada uno al vector
	        	std::istringstream iss(linea);
	                std::string num;
	                while (iss >> num) {
	                    sol1.push_back(num);
	                }
	        }
		else if (sol2.empty()) {
	                // Divide la línea en componentes y agrega cada uno al vector
	                std::istringstream iss(linea);
	                std::string num;
	                while (iss >> num) {
	                    sol2.push_back(num);
	                }
	        }
		else if (sol3.empty()) {
	                // Divide la línea en componentes y agrega cada uno al vector
	                std::istringstream iss(linea);
	                std::string num;
	                while (iss >> num) {
	                    sol3.push_back(num);
	                }
	            }
	      }
	        
	      archivoEntrada.close();
	        
	      // Transformacion de listas de str a int
	      for (const auto& str : particiones) {particionesInt.push_back(std::stoi(str));}
	      for (const auto& str : sol1) {sol1Int.push_back(std::stoi(str));}
	      for (const auto& str : sol2) {sol2Int.push_back(std::stoi(str));}
	      for (const auto& str : sol3) {sol3Int.push_back(std::stoi(str));}
	        
	      // Imprimimos la info
	      /*
	      std::cout << "Memoria: " << memoria << ", Cantidad de particiones: " << cant << ", Opcion: " << opcion << std::endl;
	      std::cout << "Particiones:" << std::endl;
	      for (const auto& particion : particionesInt) {std::cout << particion << std::endl;}
	      std::cout << "Sol1:" << std::endl;
	      for (const auto& s : sol1Int) {std::cout << s << std::endl;}
	      std::cout << "Sol2:" << std::endl;
	      for (const auto& s : sol2Int) {std::cout << s << std::endl;}
	      std::cout << "Sol3:" << std::endl;
	      for (const auto& s : sol3Int) {std::cout << s << std::endl;}
	      */
      }
};

class GestorMemoria {
private:
    int tamanoMemoria;
    std::vector<int> memoria;

    public:
	GestorMemoria(int tamano) : tamanoMemoria(tamano), memoria(tamano, -1) {
	// Inicializar la memoria con valores (-1) para indicar que esta vacia.
        }
	
    // Implementacion del algoritmo First-fit para asignar memoria.
    bool FirstFit(int procesoID, int tamano, std::vector<int> particiones){
	int resta = 0;
	for (int i = 0; i < particiones.size(); i++) {
		if (particiones[i] >= tamano){
			resta = particiones[i] - tamano;
			cambio = resta;
			pos = i;
			// std::cout << cambio << " " << pos << std::endl;
			return true;
	    	}
	}
	return false;  // No se encontró espacio adecuado para asignar memoria
    }
	
    // Implementacion del algoritmo Best-fit para asignar memoria.
    bool BestFit(int procesoID, int tamano, std::vector<int> particiones){
	int resta = 100000;
	for (int i = 0; i < particiones.size(); i++) {
    		if (particiones[i] >= tamano && particiones[i] - tamano < resta){
    			resta = std::min(resta, particiones[i] - tamano);
	        	cambio = resta;
	        	pos = i; 
	        	std::cout << cambio << " " << pos << std::endl;
    		}
	}
    	if (resta != 100000){
    		return true;
	}
	return false;  // No se encontró espacio adecuado para asignar memoria
    }
	
    // Implementacion del algoritmo Wordt-Fit para asignar memoria.
    bool WorstFit(int procesoID, int tamano, std::vector<int> particiones){
	int resta = 0;
	auto maximoIter = std::max_element(particiones.begin(), particiones.end());
	resta = *maximoIter - tamano;
	if (resta >= 0){
		cambio = resta;
	        pos = std::distance(particiones.begin(), maximoIter);
	        std::cout << cambio << " " << pos << std::endl;
	        return true;
	}
	return false;  // No se encontró espacio adecuado para asignar memoria
    }
	
    std::vector<int> liberarMemoria(std::vector<int> particiones, std::vector<int> particionOriginal){
	particiones = particionOriginal;
	return particiones;
    }
	
    void imprimirEstadoMemoria(std::vector<int> particiones){
	std::cout << "Estado de la memoria:\n";
	for (int i = 0; i < particiones.size(); i++) {
    		std::cout << particiones[i] <<std::endl;
    	}
    }
};

int main(){
	Reader reader;
	int tamanoMemoria = reader.memoria;
	int opcion = reader.opcion;
	int proceso1 = reader.sol1Int[0];
	int solicitud1 = reader.sol1Int[1];
	int proceso2 = reader.sol2Int[0];
	int solicitud2 = reader.sol2Int[1];
	int proceso3 = reader.sol3Int[0];
	int solicitud3 = reader.sol3Int[1];
	
	std::vector<int> particionesInt = reader.particionesInt;
	std::vector<int> particionOriginal = reader.particionesInt;
	
	GestorMemoria gestor(tamanoMemoria);
	
	// Asignacion o no de las solicitudes
	switch (opcion) {
	// First-Fit
        case 1:
            	std::cout << "Algoritmo de First-Fit" << std::endl;
            	if (gestor.FirstFit(proceso1, solicitud1, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso1 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso1 << std::endl;}
			
		if (gestor.FirstFit(proceso2, solicitud2, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso2 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso2 << std::endl;}
			
		if (gestor.FirstFit(proceso3, solicitud3, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso3 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso3 << std::endl;}
			
		gestor.imprimirEstadoMemoria(particionesInt);
                break;
        // Best-Fit
        case 2:
		std::cout << "Algoritmo de Best-Fit" << std::endl;
            	if (gestor.BestFit(proceso1, solicitud1, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso1 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso1 << std::endl;}
			
		if (gestor.BestFit(proceso2, solicitud2, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso2 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso2 << std::endl;}
			
		if (gestor.BestFit(proceso3, solicitud3, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso3 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso3 << std::endl;}
			
		gestor.imprimirEstadoMemoria(particionesInt);
            	break;
        //Worst-Fit
        case 3:
            	std::cout << "Algoritmo de Worst-Fit" << std::endl;
            	if (gestor.WorstFit(proceso1, solicitud1, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso1 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso1 << std::endl;}
			
		if (gestor.WorstFit(proceso2, solicitud2, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso2 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso2 << std::endl;}
			
		if (gestor.WorstFit(proceso3, solicitud3, particionesInt)) {
			std::cout << "Se logro asignar el proceso: " << proceso3 << std::endl;
			particionesInt[pos] = cambio;
			cambio = 0;
		}
		else{std::cout << "No se pudo asignar el proceso: " << proceso3 << std::endl;}
			
		gestor.imprimirEstadoMemoria(particionesInt);
            	break;
            
        default:
            	std::cout << "Opcion no valida." << std::endl;
            	break;
        }
	
	std::vector<int> free = gestor.liberarMemoria(particionesInt, particionOriginal);
	std::cout << "\n--Procesos liberado--" << std::endl;
	gestor.imprimirEstadoMemoria(free);
	return 0;
}
