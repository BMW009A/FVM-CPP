//
// Created by QCZ on 11/3/2024.
//
/*
 * File: CPPVec2CArr.cpp
 * ---------------------
 * This file contains functions to convert the std::vector to C-style array for CRS format and solver of system of
 * linear equations.
 */
#include "CPPVec2CArr.hpp"
#include "CRSMatrix.h"
#include <vector>
#include <stdexcept>

using namespace std;

/*
 * Function: Vector2Flatten
 * -------------------------
 * Flatten 2D std::vector to C-style array for the CRS format
 *
 */
double* Vector2Flatten(const vector<vector<double>>& matrix) {

    size_t rows = matrix.size();
    size_t cols = rows > 0 ? matrix[0].size() : 0;

    // Allocate a raw array to hold the flattened data
    auto* flatMatrix = new double[rows * cols];

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            flatMatrix[i * cols + j] = matrix[i][j];
        }
    }

    return flatMatrix;

}

/*
 * Function: Flatten2Vector
 * -------------------------
 * Assemble the flatten C-style array to 2D std::vector
 */
vector<vector<double>> Flatten2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols) {

    std::vector<std::vector<double>> VecOutput;

    // Convert the CRS format matrix to 2D std::vector after solving the system of linear equations.

    return VecOutput;
}