#include <fstream>
#include <string>
#include <string.h>
#include "entropia.h"


int main(int argc, char *argv[]){

  // Obtener entropia de los datasets
  double num = Entropy_dataset(argv[1]);

  std::cout << "Entropia del dataset: " << num << std::endl;

  return 0;
}
