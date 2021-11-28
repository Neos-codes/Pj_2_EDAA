#include "entropia.h"

// Lee un archivo de enteros y guarda la cantidad de apariciones
// de cada numero en un mapa
// unordered_map &map: mapa donde guardar los pares <numero, apariciones>
// string route: ruta del archivo con los datos 
int Read_in_map(std::unordered_map<int, int> &map, std::string route){
  // Para calcular elementos totales en el archivo
  int elements = 0;
  std::ifstream file(route);
  int num;
  //std::cout << "Leyendo " << route << std::endl;
  // Abrir archivo
  if(!file.is_open()){
    std::cout << "Error al abrir archivo " << route << std::endl;
    return 0;
  }
  // Pushear enteros al mapa uno por uno
  while(file >> num){
    elements++;   // Contador de elementos totales
    //std::cout << num << std::endl;
    map[num]++;
  }

  // Retornar elementos totales
  return elements;
}


// Calcula y retorna la entropia de un vector que almacena la probabilidad de
// aparicion de cada elemento
double Entropy_vector(std::vector<double> &v){

  // Calcular entropia del dataset
  double H = 0;
  for(auto e: v){
    H += e * (log(e) / log(2));  // Se usa cambio de base para log_2(e)
  }

  H *= -1;

  return H;
  
}

// Retorna la entropia de todos los archivos de extension definida (por default
// .txt) en un directorio.
// string route: ruta local del directorio con elementos para calcular entropia
double Entropy_dataset(std::string route){

  std::unordered_map<int, int> data;
  int elements = 0;
  // Creamos estructura para guardar archivos 1 por 1
  struct dirent *dir;
  // Abrimos el directorio de la ruta ingresada
  DIR *dp = opendir(route.c_str());
  
  if(dp != NULL){
    // Inspeccionamos archivos
    while((dir = readdir(dp)) != NULL){
      std::string *doc = new std::string(dir -> d_name);

      // Si son la carpeta raiz o la padre, ignorar
      if(!doc -> compare("..") || !doc -> compare("."))
	continue;
      // Verificamos extension, solo los .txt seran leidos
      std::string *ext = new std::string(&dir -> d_name[doc -> size() - 4]);
      //std::cout << "Extension leida: " << *ext << std::endl;
      if(!ext -> compare(".txt")){
	// Abrir archivo
	// Elements es para calcular los elementos totales en el dataset
	elements += Read_in_map(data, route + "/" + std::string(dir -> d_name));
      }
      
      // Limpiar memoria dinamica
      delete doc;
      delete ext;
    }
  }

  // Se guardaran en un vector todas las probabilidades
  std::vector<double> probs(data.size());

  // Calculamos las probabilidades
  int i = 0;
  for(auto e: data){
    // Apariciones del elemento i / casos totales
    probs[i] = (double)e.second / elements;
    i++;
  }

  // Retornar entropia del dataset
  return Entropy_vector(probs);
}
