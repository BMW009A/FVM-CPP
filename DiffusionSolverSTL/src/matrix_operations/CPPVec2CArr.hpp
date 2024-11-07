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

/* Generalized primary template for converting a `std::vector` to a C-style array
 *
 * This template handles 1D and 2D vectors by specializing the function for each case.
 * It uses `std::unique_ptr` to automatically manage memory, returning a pointer
 * to the allocated C-style array.
 *
 * Template Parameters:
 *   - T: The type of elements in the vector (e.g., double, float)
 *   - VectorType: The type of the vector to be converted (1D or 2D vector)
 *
 * Parameters:
 *   - vec: The C++ `std::vector` to be converted
 *
 * Returns:
 *   A `std::unique_ptr<T[]>` pointing to a dynamically allocated C-style array
 */
template<typename T, typename VectorType>
std::unique_ptr<T[]> Vector2CArray(const VectorType& vec);

/* Specialization for 1D vector (std::vector<T>) to C-style array (T*)
 *
 * Parameters:
 *   - vec: The 1D vector to be converted
 *
 * Returns:
 *   A `std::unique_ptr<T[]>` holding the C-style array with the same data as 'vec'
 */
template <typename T>
std::unique_ptr<T[]> Vector2CArray(const std::vector<T>& vec) {
    size_t size = vec.size();
    std::unique_ptr<T[]> arr = std::make_unique<T[]>(size);  // Allocate memory for C-style array

    for (size_t i = 0; i < size; ++i) {
        arr[i] = vec[i];  // Copy elements from std::array to C array
    }

    return arr;  // Return the pointer to the allocated C-style array
}

/* Specialization for 1D vector (std::vector<T>) to C-style array (T*)
 *
 * Parameters:
 *   - vec: The 2D vector to be converted
 *
 * Returns:
 *   A `std::unique_ptr<T[]>` holding the C-style array with the same data as 'vec'
 */
template <typename T>
std::unique_ptr<T[]> Vector2CArray(const std::vector<std::vector<T>>& vec) {
    size_t rows = vec.size();
    size_t cols = vec[0].size();

    // Allocate memory for a flattened C-style array (rows * cols)
    std::unique_ptr<T[]> arr = std::make_unique<T[]>(rows * cols);

    // Copy elements from std::vector<std::vector<double>> to the flattened C array
    for (size_t i = 0; i < rows; ++i) {
        std::copy(vec[i].begin(), vec[i].end(), arr.get() + i * cols);
    }

    return arr;
}

/* Generalized primary template for converting a CRSMatrix (C-style array) to `std::vector`
 *
 * This template supports conversion of CRSMatrix format to both 1D and 2D vectors,
 * reconstructing the full matrix with default values (0) for missing elements.
 *
 * Template Parameters:
 *   - T: The type of elements in the output vector (e.g., double, float)
 *   - ReturnType: The type of `std::vector` to return (1D or 2D vector)
 *
 * Parameters:
 *   - crs_matrix: Pointer to the CRSMatrix structure containing the sparse matrix data
 *   - rows: Number of rows in the original matrix
 *   - cols: Number of columns in the original matrix
 *
 * Returns:
 *   A fully populated 1D or 2D `std::vector` representing the dense form of the matrix
 */
template<typename T, typename ReturnType>
ReturnType CArray2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols);

/* Specialization for converting CRSMatrix to a 2D `std::vector<std::vector<T>>`
 *
 * This function reconstructs the full 2D matrix from CRS format, populating non-zero
 * elements from `crs_matrix` and filling in zeros for all other positions.
 *
 * Parameters:
 *   - crs_matrix: Pointer to the CRSMatrix structure containing the sparse matrix data
 *   - rows: Number of rows in the original matrix
 *   - cols: Number of columns in the original matrix
 *
 * Returns:
 *   A `std::vector<std::vector<T>>` representing the dense form of the CRS matrix
 */
template<typename T>
std::vector<std::vector<double>> CArray2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    // Check the inputs' validation
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

/* Specialization for converting CRSMatrix to a 1D `std::vector<T>`
 *
 * This function reconstructs the flattened 1D representation of a dense matrix from
 * CRS format, storing elements in row-major order.
 *
 * Parameters:
 *   - crs_matrix: Pointer to the CRSMatrix structure containing the sparse matrix data
 *   - rows: Number of rows in the original matrix
 *   - cols: Number of columns in the original matrix
 *
 * Returns:
 *   A `std::vector<T>` representing the dense form of the CRS matrix in row-major order
 */
template<typename T>
std::vector<T> CArray2Vector(CRSMatrix* crs_matrix, size_t rows, size_t cols) {
    // Check the inputs' validation
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

#endif //PROJECT_02_FVM_CPPVEC2CARR_HPP