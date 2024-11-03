//
// Created by QCZ on 11/3/2024.
//

#ifndef PROJECT_02_FVM_CPPVEC2CARR_HPP
#define PROJECT_02_FVM_CPPVEC2CARR_HPP

#include <vector>
#include "CRSMatrix.h"
using namespace std;

double* Vector2Flatten(const vector<vector<double>>& matrix);

vector<vector<double>> Flatten2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols)

#endif //PROJECT_02_FVM_CPPVEC2CARR_HPP
