#include <iostream>
#include <sdsl/vectors.hpp>       // int_vector y bit_vector
#include <sdsl/bit_vectors.hpp>   // rrr_vector y sd_vector
#include "data_utils.h"
#include <sdsl/k2_tree.hpp>
#include <string>
// Notas: solo se puede usar sdsl::util::bit_compress(v) con un int_vector v

int main(int argc, char *argv[]){
  
  if(argc < 2){
    std::cout << "A route to dataset is needed\nExample: ./ej2_ dataset/\n";
    return 0;
  }
  
  std::string route(argv[1]);

  // Elementos ejercicio 3 (contiene el 1 y el 2)

  // Crear los bitmaps de cada dataset
  sdsl::bit_vector b_8(8 * 8 * 120);
  sdsl::bit_vector b_128(128 * 128 * 120);
  sdsl::bit_vector b_512(512 * 512 * 120);

  // Crear los int_vectors de cada dataset
  sdsl::int_vector<> *v_8 = Load_dataset(b_8, route + "/8x8");  
  sdsl::int_vector<> *v_128 = Load_dataset(b_128, route + "/128x128");
  sdsl::int_vector<> *v_512 = Load_dataset(b_512, route + "/512x512");

  // Elementos ejercicio 4
  
  // rrr_vectors (dan un espacio mas pequeño)
  sdsl::rrr_vector<> rrr_8(b_8);
  sdsl::rrr_vector<> rrr_128(b_128);
  sdsl::rrr_vector<> rrr_512(b_512);

  // Soportar ranks para rrr_vectors
  sdsl::rrr_vector<>::rank_1_type rrr8_rank(&rrr_8);
  sdsl::rrr_vector<>::rank_1_type rrr128_rank(&rrr_128);
  sdsl::rrr_vector<>::rank_1_type rrr512_rank(&rrr_512);


  // Pruebas con ranks
  std::cout << "Prueba con ranks\n";
  // Para rank, la posicion 0 de un vector es la posicion 1
  std::cout << (*v_512)[rrr512_rank(27) - 1] << std::endl;

  // Espacio que ocupan los rrr_vector
  std::cout << "rrr_8: " << size_in_bytes(rrr_8) << std::endl;
  std::cout << "rrr_128: " << size_in_bytes(rrr_128) << std::endl;
  std::cout << "rrr_512: " << size_in_bytes(rrr_512) << std::endl;


  // Elementos ejercicio 5

  // Matrices de adyacencia
  std::vector<std::vector<int>> vadj_8;
  std::vector<std::vector<int>> vadj_128;
  std::vector<std::vector<int>> vadj_512;

  // Tamaños de los k2_tree para cada matriz de cada dataset
  std::vector<int> k2_size8;
  std::vector<int> k2_size128;
  std::vector<int> k2_size512;

  sdsl::k2_tree<2> *k2;
  
  // En cada dataset hay 120 matrices
  for(int t = 1; t < 120; t++){   // t = z
    // Para las matrices de 8x8 los elementos se cargan en un vector de vectores
    // Que luego van a parar a un k2 tree
    for(int i = 0; i < 8; i++){   // i = fila
      std::vector<int> aux; 
      for(int j = 0; j < 8; j++){  // j = col
	int t_1 = (*v_8)[rrr8_rank(C_3Dto1D(t - 1, i, j, 8)) - 1];
	int t_ = (*v_8)[rrr8_rank(C_3Dto1D(t, i, j, 8)) - 1];
	if(t_1 != t_)
	  aux.push_back(1);
	else
	  aux.push_back(0);
      }
      vadj_8.push_back(aux);;
    }
    // Crear un k2_tree para la matriz de 8x8 en instante t
    k2 = new sdsl::k2_tree<2>(vadj_8);
    // Pushear tamanio a un vector de tamanios de k2_trees para 8x8
    k2_size8.push_back(size_in_bytes(*k2));
    // Eliminar el k2_tree una vez se guarda su tamanio
    delete k2;

    Clean_mat_vec(vadj_8);
    // Para las matrices de 128x128, lo mismo que para 8x8
    for(int i = 0; i < 128; i++){
      std::vector<int> aux;
      for(int j = 0; j < 128; j++){
	int t_1 = (*v_128)[rrr128_rank(C_3Dto1D(t - 1, i, j, 128)) - 1];
	int t_ = (*v_128)[rrr128_rank(C_3Dto1D(t, i, j, 128)) - 1];
	if(t_1 != t_)
	  aux.push_back(1);
	else
	  aux.push_back(0);
      }
      vadj_128.push_back(aux);
    }
    k2 = new sdsl::k2_tree<2>(vadj_128);
    k2_size128.push_back(size_in_bytes(*k2));
    delete k2;

    Clean_mat_vec(vadj_128);
    
    // Para las matrices de 512x512, lo mismo que para las anteriores
    for(int i = 0; i < 512; i++){
      std::vector<int> aux;
      for(int j = 0; j < 512; j++){
	int t_1 = (*v_512)[rrr512_rank(C_3Dto1D(t - 1, i, j, 512)) - 1];
	int t_ = (*v_512)[rrr512_rank(C_3Dto1D(t, i, j, 512)) - 1];
	if(t_1 != t_)
	  aux.push_back(1);
	else
	  aux.push_back(0);
      }
      vadj_512.push_back(aux);
    }
    k2 = new sdsl::k2_tree<2>(vadj_512);
    k2_size512.push_back(size_in_bytes(*k2));
    delete k2;

    Clean_mat_vec(vadj_512);
  }

  Print_vector(k2_size8, "k2_8");
  Print_vector(k2_size128, "k2_128");
  Print_vector(k2_size512, "k2_512");

  /*
  std::cout << "Probando dataset diff\n";

  sdsl::int_vector<> base(8 * 8);
  sdsl::bit_vector bmap(8 * 8 * 119);
  
  Load_dataset_diff(bmap, route + "/8x8", base);
  */
  
  return 0;
}
