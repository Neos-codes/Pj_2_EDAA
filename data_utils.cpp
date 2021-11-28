#include "data_utils.h"

// En esta funcion se carga cada matriz y si hay diferencias de coloca un 1 en el vector y si se repite un 0
// Tambien retorna un std::vector<int> con los elementos sin repetir, en la función
// vector_2_int_vector se parsea el std::vector a un int_vector
int Load_mat_2_int_vec(std::vector<int> &e, int n_elements, sdsl::bit_vector &b, std::string route){
  std::ifstream file(route);
  int num;
  // Abrir archivo
  if(!file.is_open()){
    std::cout << "Error al abrir archivo " << route << std::endl;
    return n_elements;
  }

  // --- Agregar enteros al int_vector

  
  // El primer elemento siempre se guarda elemento en int_vector y en bitmap como 1
  if(e.size() == 0){
    file >> num;
    e.push_back(num);
    b[n_elements] = 1;
    //std::cout << "Primer elemento: " << e[e.size() - 1] << std::endl;
    // Incrementar cantidad de elementos
    n_elements++;
  }
  // Para el resto se verifica en la marcha
  while(file >> num){
    // Si el elemento actual es igual al anterior, en bitmap se guarda un 0
    if(num == e[e.size() - 1]){
      b[n_elements] = 0;
      //std::cout << "Push 0: " << e[e.size() - 1] << " == " << num << std::endl;
    }
  // Si es distinto al anterior, se guarda elemento en int_vector y en bitmap como 1
    else{
      b[n_elements] = 1;
      //std::cout << "Push 1: " << e[e.size() - 1] << " != " << num << std::endl;
      e.push_back(num);
    }
    // Incrementar cantidad de elementos
    n_elements++;
  }
  // retorna elementos en el int_vector
  return n_elements;
}

sdsl::int_vector<> *vector_2_int_vector(std::vector<int> &e){

  sdsl::int_vector<> *vec = new sdsl::int_vector<>(e.size());

  int e_size = e.size();
  for(int i = 0; i < e_size; i++){
    (*vec)[i] = e[i];
  }

  return vec;
}


// Funcion principal para cargar los datasets y crear un int_vec con los elementos
// que no se repiten
// Recibe como parametro un bitmap &b que almacenará 0's y 1's dependiendo si los
// elementos dejan de repetirse
sdsl::int_vector<> *Load_dataset(sdsl::bit_vector &b, std::string route){

  std::cout << "Loading dataset... " << route << std::endl;
  std::vector<int> e;
  std::vector<std::string> docs;
  
  int elements = 0;
  bool has_ext = false;
  // Estructura para guardar archivos
  struct dirent *dir;
  // Abrir directorio de ruta ingresada
  DIR *dp = opendir(route.c_str());

  if(dp != NULL){
    // Inspeccionar archivos
    while((dir = readdir(dp)) != NULL){
      int pos;
      std::string doc(dir -> d_name);
      //std::cout << doc << std::endl;
      // Filtrar referencias a otras carpetas
      if(!doc.compare("..") || !doc.compare(".") || doc.size() < 4)
	continue;
      // Verificamos extension si tamanio es > 3 por sizeof(".txt") = 4
      std::string ext(dir -> d_name + doc.size() - 4);
      //std::cout << ext << std::endl;
      if(!ext.compare(".txt")){
	// Aqui leemos el nombre del archivo y se lo damos a un vector de strings
	docs.push_back(doc);
	//elements = Load_mat_2_int_vec(e, elements, b, route + "/" + doc);
      }
    }

    // Ordenamos alfabeticamente los documentos para mantener el orden para M_i
    sort(docs.begin(), docs.end());

    // Cargar todos los archivos en un int_vec
    for(int i = 0; i < docs.size(); i++){
      //std::cout << docs[i] << std::endl;
      elements = Load_mat_2_int_vec(e, elements, b, route + "/" + docs[i]);
    }
  }

  // Retornar un int_vec de todas las matrices
  return vector_2_int_vector(e);
}

// Matriz para limpiar matrices auxiliares
void Clean_mat_vec(std::vector<std::vector<int>> &mat){

  for(int i = 0; i < mat.size(); i++){
    mat[i].clear();
  }
  mat.clear();
}

// Convierte una coordenada del arreglo de matrices a un arreglo normal
unsigned int C_3Dto1D(int t, int i, int j, int n){
  return t * n * n + i * n + j + 1;
}

// Imprimer un vector
void Print_vector(std::vector<int> &v, std::string name){

  std::cout << name << std::endl;
  
  for(int i = 0; i < v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  
}
