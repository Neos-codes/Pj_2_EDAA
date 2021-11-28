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
  // retorna elementos en el bitmap
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


// Retorna los nombres de los archivos en el dataset ordenados alfabeticamente
// para mantener el orden de las matrices en el tiempo
std::vector<std::string> Dataset_docs(std::string route){

  // Vector de nombres de archivos
  std::vector<std::string> docs;

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
      }
    }
  }
    // Ordenamos alfabeticamente los documentos para mantener el orden para M_i
    sort(docs.begin(), docs.end());

    return docs;
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

  docs = Dataset_docs(route);

    // Cargar todos los archivos en un int_vec
    for(int i = 0; i < docs.size(); i++){
      //std::cout << docs[i] << std::endl;
      elements = Load_mat_2_int_vec(e, elements, b, route + "/" + docs[i]);
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

int Mats_diff(sdsl::bit_vector &b, std::vector<int> &diffs, int n_elements, std::string route_1, std::string route){

  // Abrimos docs con matrices del dataset a calcular diferencia
  std::ifstream mat_1(route_1);   // matriz en t - 1
  std::ifstream mat(route);       // matriz en t

  int num;     // valor (x_t, y_t)
  int num_1;   // valor (x_(t-1), y_(t-1)

  // Si es el primer elemento que se lee, obligatoriamente se pushea un 1 al bitmap
  // y la diferencia al vector de diferencias
  if(diffs.size() == 0){
    std::cout << "Diff size = " << diffs.size() << std::endl;
    // Tomamos numeros para calcular diferencia
    mat >> num;
    mat_1 >> num_1;

    // Pushear 1 al bitmap
    b[n_elements] = 1;
    // Pushear diferencia al vector de diferencias
    diffs.push_back(num - num_1);
    n_elements++;
  }

  // Extraemos un numero de la matriz actual
  while(mat >> num){
    // Extraemos un numero de la matriz anterior
    mat_1 >> num_1;

    // Obtener diferencia
    int dif = num - num_1;
    
    // Si la diferencia entre los 2 elementos actuales es igual a la diferencia
    // anterior, pushear un 0 en bitmap por ser elemento repetido
    if(dif == diffs.back())
      b[n_elements] = 0;
    // Si las diferencias son distintas, pushear un 1 en bitmap y la diferencia
    // en el vector de diferencias
    else{
      b[n_elements] = 1;
      diffs.push_back(num - num_1);
      //std::cout << "num: " << num << " num_1: " << num_1 << " dif: " << diffs.back() << std::endl;
    }
    n_elements++;
  }

  // Retornamos la cantidad de elementos actuales que tiene el bitmap
  return n_elements;
}

sdsl::int_vector<> *Load_dataset_diff(sdsl::bit_vector &b, std::string route, sdsl::int_vector<> &base){

  std::cout << "Loading dataset diff... " << route << std::endl;
  std::vector<int> e;
  std::vector<std::string> docs;
  
  int elements = 0;

  docs = Dataset_docs(route);

  // Cargar matriz en t = 0 en raw para luego operar sobre ella e implementar
  // el ejercicio 7
  std::ifstream file(route + "/" + docs[0]);
  int num;
  // Abrir archivo
  if(!file.is_open()){
    std::cout << "Error al abrir archivo " << route << std::endl;
    return 0;
  }

  int it = 0;
  while(file >> num){
    base[it] = num;     // El int_vector base debe tener tamanio definido
    it++;
  }
  
  // Cerrar archivo
  file.close();

  // Creamos un vector de enteros que guardará las diferencias de temperaturas
  // entre M_i y M_(i-1)
  std::vector<int> diffs;
  
  // Cargar diferencias en vector de diferencias y llenar el bitmap por cada matriz
  // en el dataset
  for(int i = 1; i < 120; i++)
    elements = Mats_diff(b, diffs, elements, route + "/" + docs[i - 1], route + "/" + docs[i]);

  //Print_vector(diffs, "Diff vector");
  
  // Retornamos un int_vector con las diferencias de las matrices M_i  y M_(i-1)
  return vector_2_int_vector(diffs);
}
