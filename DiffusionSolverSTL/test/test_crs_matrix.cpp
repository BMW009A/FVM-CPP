//
// Created by QCZ on 10/24/2024.
//
// Created by QCZ on 10/24/2024.
//
/*
 * File: test_crs_matrix.cpp
 * -------------------------
 * This file contains unit tests for the CRS (Compressed Row Storage) matrix storage implementation
 * defined in 'matrix_operations/CRSMatrix.c'. The tests evaluate the correct conversion of dense
 * matrices to CRS format and check edge cases, normal cases, and performance.
 *
 * The following test cases are included:
 * 1. Small size sparse matrix
 * 2. Medium size sparse matrix
 * 3. Large size sparse matrix
 * 4. Extreme large sparse matrix (for performance testing)
 * 5. Edge cases: all-zero matrix, and a matrix with a large number of non-zero elements.
 */

#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <random>
#include "CRSMatrix.h"

using namespace std;
// Helper function to generate a large sparse matrix
vector<vector<double>> gen_large_sparse_matrix(size_t rows, size_t cols, double sparsity = 0.01) {

    vector<vector<double>> dense(rows, vector<double>(cols, 0.0));
    double non_zero_elements = static_cast<double>(rows) * static_cast<double>(cols) * sparsity;
    auto non_zero_elements_int = static_cast<size_t>(non_zero_elements); // Convert to integer if necessary

    // Set up random number generator
    random_device rd;        // Seed generator
    mt19937 gen(rd());       // Mersenne Twister engine seeded with rd()
    uniform_int_distribution<> row_dist(0, static_cast<int>(rows) - 1);
    uniform_int_distribution<> col_dist(0, static_cast<int>(cols) - 1);
    uniform_int_distribution<> value_dist(1, 100);    // Values between 1 and 100

    for (size_t i = 0; i < non_zero_elements_int; ++i) {

        size_t row = row_dist(gen);
        size_t col = col_dist(gen);

        dense[row][col] = static_cast<int>(value_dist(gen));

    }

    return dense;

}

// Test for the small size of sparse matrix
// Verifies that a small 3x3 sparse matrix is correctly converted to CRS format.
TEST(CRSTest, smallMatrixTest) {

}

// Test for the medium size of sparse matrix
// Verifies that a medium 100x100 sparse matrix is correctly converted to CRS format.
TEST(CRSTest, MiddleMatrixTest) {

}

// Test for the large size of sparse matrix
// Verifies that a medium 1000x1000 sparse matrix is correctly converted to CRS format.
TEST(CRSTest, LargeMatrixTest1000) {

}
// Test for the large size of sparse matrix
// Verifies that a medium 5000x5000 sparse matrix is correctly converted to CRS format.
TEST(CRSTest, LargeMatrixTest5000) {

}

// Test for an extremely large sparse matrix to assess performance and correctness
// under high load (e.g., millions of entries).
TEST(CRSTest, ExtremeMatrixTest) {
    // Test implementation goes here
}

// Pressure test to measure performance on large matrices
// Measures the time taken for specific operations on very large sparse matrices
// to evaluate efficiency and scalability of the CRS conversion.
TEST(CRSTest, PressureMatrixTest) {
    // Test implementation goes here
}