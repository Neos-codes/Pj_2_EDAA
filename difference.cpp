#include <iostream>
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
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
  sdsl::bit_vector b_8(8 * 8 * 119);
  sdsl::int_vector<> base_8(8 * 8);
  sdsl::int_vector<> *v_8 = Load_dataset_diff(b_8, route + "/8x8", base_8);
  
  /*
  // Para dataset 128x128
  sdsl::bit_vector b_128(128 * 128 * 119);
  sdsl::int_vector<> base_128(128 * 128);
  sdsl::int_vector<> *v_128 = Load_dataset_diff(b_128, route+"/128x128", base_128);

  // Para dataset 512x512
  sdsl::bit_vector b_512(512 * 512 * 119);
  sdsl::int_vector<> base_512(512 * 512);
  sdsl::int_vector<> *v_512 = Load_dataset_diff(b_512,route+"/512x512", base_512);

  */

  
  // Nota: no se pueden representar negativos en int_vector
  // Para sortear el problema de las diferencias negativas, las temperaturas al
  // tener un dominio acotado, se hace un casteo simple de uint64_t a int64_t
  // Para efectos de este experimento funciona correctamente
  
  // Se utilizará esta mask para verificar numeros negativos
  uint64_t mask = (uint64_t)1 << 63;

  // Se castea de uint64_t a int64_t
  for(int i = 0; i < v_8 -> size(); i++){
    std::cout << (int64_t)(*v_8)[i] << " ";
  }
  std::cout << std::endl;

  // Para la solucion del problema 7, solo de debe aplicar soportar rank e ir
  // sumandole al valor de la matriz base las diferencias en el vector v_n

  return 0;
}
