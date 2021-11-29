#include <iostream>
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include "compress_diff.cpp"
#include "data_utils.h"
#include <string>

int main(int argc, char *argv[]){

  if(argc < 2){
    std::cout << "A route to dataset is needed\nExample: ./ej_6 dataset\n";
    return 0;
  }

  std::string route(argv[1]);

  // Para cada dataset creamos un bitmap para los elementos repetidos, un int vector
  // que almacena la primera matriz de cada dataset
  // y un int vector que almacena los elementos distintos de las diferencias

  // Para dataset 8x8
  compress_diff data_8(8, route + "/8x8");
  //data_8.print_base();
  //data_8.print_diff_vector();
  std::cout << "\nCompressed Memory used: " << data_8.memory_used() << " MB\n";
  std::cout << "Uncompressed memory used: " << data_8.uncompressed_memory_used() << " MB\n";
  std::cout << "Compression ratio: " << data_8.memory_used() / data_8.uncompressed_memory_used() << std::endl << std::endl;
  
  // Para dataset 128x128
  compress_diff data_128(128, route + "/128x128");
  std::cout << "\nCompressed Memory used: " << data_128.memory_used() << " MB\n";
  std::cout << "Uncompressed memory used: " << data_128.uncompressed_memory_used() << " MB\n";
  std::cout << "Compression ratio: " << data_128.memory_used() / data_128.uncompressed_memory_used() << std::endl << std::endl;
  
  
  // Para dataset 512x512
  compress_diff data_512(512, route + "/512x512");
  std::cout << "\nCompressed Memory used: " << data_512.memory_used() << " MB\n";
  std::cout << "Uncompressed memory used: " << data_512.uncompressed_memory_used() << " MB\n";
  std::cout << "Compression ratio: " << data_512.memory_used() / data_512.uncompressed_memory_used() << std::endl << std::endl;
  
  
  // Nota: no se pueden representar negativos en int_vector
  // Para sortear el problema de las diferencias negativas, las temperaturas al
  // tener un dominio acotado, se hace un casteo simple de uint64_t a int64_t
  // Para efectos de este experimento funciona correctamente
  
  // Se utilizará esta mask para verificar numeros negativos
  uint64_t mask = (uint64_t)1 << 63;


  
  
  /*
  // Se castea de uint64_t a int64_t
  for(int i = 0; i < v_8 -> size(); i++){
    std::cout << (int64_t)(*v_8)[i] << " ";
  }
  std::cout << std::endl;
  */

  // Para la solucion del problema 7, solo de debe aplicar soportar rank e ir
  // sumandole al valor de la matriz base las diferencias en el vector v_n

  return 0;
}
