//
// Created by QCZ on 11/3/2024.
//
/*
 * File: CPPVec2CArr.hpp
 * ---------------------
 *
 */
#ifndef PROJECT_02_FVM_CPPVEC2CARR_HPP
#define PROJECT_02_FVM_CPPVEC2CARR_HPP

#include <vector>
#include "CRSMatrix.h"

using namespace std;

double* Vector2Flatten(const vector<vector<double>>& matrix);

// Primary template declaration
template<typename ReturnType>
ReturnType Flatten2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols);

// Specialization for 2D vector: std::vector<std::vector<double>>
template<>
vector<vector<double>> Flatten2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    vector<vector<double>> result(rows, vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = crs_matrix->row_ptr[i]; j < crs_matrix->row_ptr[i + 1]; ++j) {
            result[i][j] = crs_matrix->values[j];
        }
    }

    return result;
}

// Specialization for 1D vector: std::vector<double>
template<>
vector<double> Flatten2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    vector<double> result(rows * cols, 0.0);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = crs_matrix->row_ptr[i]; j < crs_matrix->row_ptr[i + 1]; ++j) {
            result[i * cols + crs_matrix->col_idx[j]] = crs_matrix->values[j];
        }
    }
    return result;
}

#endif //PROJECT_02_FVM_CPPVEC2CARR_HPP
