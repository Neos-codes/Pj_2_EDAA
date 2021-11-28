#ifndef ENTROPIA_H
#define ENTROPIA_H

#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <unordered_map>
#include <vector>
#include <math.h>

int Read_in_map(std::unordered_map<int, int> &map, std::string route);
double Entropy_vector(std::vector<double> &v);
double Entropy_dataset(std::string route);


#endif
