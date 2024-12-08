//
// Created by QCZ on 11/3/2024.
//
/*
 * File: CPPVec2CArr.hpp
 * ---------------------
 * This header file provides utility functions for converting between C++ `std::vector`
 * types and C-style arrays. It supports both 1D and 2D vector conversions, allowing
 * data to be passed efficiently between C++ and C components, such as CRS matrix operations
 * in linear algebra computations.
 */

#ifndef PROJECT_02_FVM_CPPVEC2CARR_HPP
#define PROJECT_02_FVM_CPPVEC2CARR_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "CRSMatrix.h"

// Convert a 1D `std::vector<T>` to a dynamically allocated C-style array (T*).
// The function returns a `std::unique_ptr<T[]>` that holds the C-style array.
//
// Template Parameters:
//   - T: The type of elements in the vector
//
// Parameters:
//   - vec: The 1D vector to be converted
//
// Returns:
//   A `std::unique_ptr<T[]>` holding the C-style array with the same data as `vec`

template <typename T>
std::unique_ptr<T[]> Vector2CArray(const std::vector<T>& vec) {
    size_t size = vec.size();
    std::unique_ptr<T[]> arr = std::make_unique<T[]>(size);  // Allocate memory

    for (size_t i = 0; i < size; ++i) {
        arr[i] = vec[i];  // Copy elements from vector to array
    }

    return arr;
}

// Convert a 2D `std::vector<std::vector<T>>` to a flattened C-style array (T*).
// Returns a `std::unique_ptr<T[]>` that holds the array in row-major order.
//
// Template Parameters:
//   - T: The type of elements in the vector
//
// Parameters:
//   - vec: The 2D vector to be converted
//
// Returns:
//   A `std::unique_ptr<T[]>` holding the flattened C-style array with the same data as `vec`
template <typename T>
std::unique_ptr<T[]> Vector2CArray(const std::vector<std::vector<T>>& vec) {
size_t rows = vec.size();
size_t cols = vec[0].size();

std::unique_ptr<T[]> arr = std::make_unique<T[]>(rows * cols);

for (size_t i = 0; i < rows; ++i) {
std::copy(vec[i].begin(), vec[i].end(), arr.get() + i * cols);
}

return arr;
}

// Convert a CRSMatrix (C-style array) to a 2D `std::vector<std::vector<T>>`.
// This function reconstructs a dense 2D matrix from the CRS format.
//
// Template Parameters:
//   - T: The type of elements in the output vector
//
// Parameters:
//   - crs_matrix: Pointer to the CRSMatrix structure containing sparse matrix data
//   - rows: Number of rows in the matrix
//   - cols: Number of columns in the matrix
//
// Returns:
//   A `std::vector<std::vector<T>>` representing the dense matrix
template <typename T>
std::vector<std::vector<T>> CArray2Vector(const CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    if (!crs_matrix) {
        throw std::invalid_argument("crs_matrix is NULL");
    }
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Invalid matrix dimensions.");
    }

    std::vector<std::vector<T>> result(rows, std::vector<T>(cols, static_cast<T>(0)));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = crs_matrix->row_ptr[i]; j < crs_matrix->row_ptr[i + 1]; ++j) {
            result[i][crs_matrix->col_idx[j]] = static_cast<T>(crs_matrix->values[j]);
        }
    }

    return result;
}

// Convert a CRSMatrix (C-style array) to a flattened 1D `std::vector<T>`.
// This function reconstructs a dense 1D representation of a matrix in row-major order.
//
// Template Parameters:
//   - T: The type of elements in the output vector
//
// Parameters:
//   - crs_matrix: Pointer to the CRSMatrix structure containing sparse matrix data
//   - rows: Number of rows in the matrix
//   - cols: Number of columns in the matrix
//
// Returns:
//   A `std::vector<T>` representing the dense matrix in row-major order
template <typename T>
std::vector<T> CArray2Vector(const CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    if (!crs_matrix) {
        throw std::invalid_argument("crs_matrix is NULL");
    }
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Invalid matrix dimensions.");
    }

    std::vector<T> result(rows * cols, static_cast<T>(0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = crs_matrix->row_ptr[i]; j < crs_matrix->row_ptr[i + 1]; ++j) {
            result[i * cols + crs_matrix->col_idx[j]] = static_cast<T>(crs_matrix->values[j]);
        }
    }
    return result;
}

#endif // PROJECT_02_FVM_CPPVEC2CARR_HPP
