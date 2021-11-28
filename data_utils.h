#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sdsl/vectors.hpp>

int Load_mat_2_int_vec(std::vector<int> &e, int n_elements, sdsl::bit_vector &b, std::string route);

sdsl::int_vector<> *vector_2_int_vector(std::vector<int> &e);

std::vector<std::string> Dataset_docs(std::string route);

sdsl::int_vector<> *Load_dataset(sdsl::bit_vector &b, std::string route);

void Clean_mat_vec(std::vector<std::vector<int>> &mat);

unsigned int C_3Dto1D(int t, int i, int j, int n);

void Print_vector(std::vector<int> &v, std::string name);

int Mats_diff(sdsl::bit_vector &b, std::vector<int> &diffs, int n_elements, std::string route_1, std::string route);

sdsl::int_vector<> *Load_dataset_diff(sdsl::bit_vector &b, std::string route, sdsl::int_vector<> &base);


#endif
