#ifndef COMPRESS_DIFF
#define COMPRESS_DIFF

#include <iostream>
#include "data_utils.h"
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include <string>

class compress_diff{

 private:
  // Variables
  sdsl::rrr_vector<> r;     // Guarda el bitmap en un rrr_vector para usar rank
  sdsl::int_vector<> base;  // Guarda la matriz base
  sdsl::int_vector<> v;    // Guarda el vector con elementos sin repeticion
  
 public:
  // Variables
  int dim;      // Dimensiones de la matriz del dataset

  // Constructor
  compress_diff(int dim, std::string route){
    // Auxiliares para crear estructuras
    sdsl::int_vector<> *aux;
    sdsl::bit_vector *b = new sdsl::bit_vector(dim * dim * 119);
    sdsl::rrr_vector<> *r_aux;
    // Guardar dimension de las matrices
    this -> dim = dim * dim;
    // Guardar matriz base
    base.resize(dim * dim);
    // Cargar dataset
    aux = Load_dataset_diff(*b, route, base);
    // Guardar dataset en v
    v = *aux;
    // Crear rrr_vector para soportar ranks eventualmente
    r_aux = new sdsl::rrr_vector<>(*b);
    r = *r_aux;
    // Limpiar memoria de auxiliares
    delete aux;
    delete b;
    delete r_aux;
    // Comprimir vectores
    sdsl::util::bit_compress(base);
    sdsl::util::bit_compress(v);
  }

  // Printea la matriz base del conjunto
  void print_base(){
    for(int i = 0; i < dim; i++){
      for(int j = 0; j < dim; j++){
	std::cout << base[i] << " ";
      }
      std::cout << std::endl;
    }
  }

  // Printea el vector con las diferencias cuando las posiciones de las matrices
  // son diferentes
  void print_diff_vector(){
    std::cout << "Vector with differences:\n";
    for(int i = 0; i < v.size(); i++){
      std::cout << (int64_t)v[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }

  // Retorna sizeof in bytes de la matriz base
  uint64_t base_size(){
    return size_in_bytes(base);
  }

  // Retorna el tamanio en bytes del vector con diferencias
  uint64_t diff_vector_size(){
    return size_in_bytes(v);
  }


  // Retorna la matriz de adyacencia para el k2_tree en el instante t. t > 1
  std::vector<std::vector<int>> *adj_matrix(int t){
    // Si se ingresa un t no valido, retornar nulo
    if(t < 1 || t > 120){
      std::cout << "t debe estar en el intervalo [1, 120]\n";
      return NULL;
    }

    // Soportamos la operanción rank
    sdsl::rrr_vector<>::rank_1_type rank(&r);
    
    std::vector<std::vector<int>> adj;
    t -= 1;
    

    
    
  }

};


#endif
