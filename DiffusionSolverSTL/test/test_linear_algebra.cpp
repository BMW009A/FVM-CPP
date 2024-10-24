//
// Created by QCZ on 10/4/2024.
//
/*
 * File: test_linear_algebra.cpp
 * -----------------------------
 * This file contains unit tests for the linear algebra functions implemented
 * in 'linear_algebra.c'. The tests include:
 *
 * 1. Matrix-vector multiplication (mat_vec_mult):
 *    - Tests multiplication for small and large matrices.
 *    - Cover edge cases like identity matrices and all-one vectors.
 *    - Tests empty matrices.
 *
 * 2. Dot product (dot_product):
 *    - Tests the dot product for vectors of varying sizes.
 *
 * 3. Vector subtraction (vec_subtract):
 *    - Tests element-wise subtraction for vectors of different sizes.
 *
 * These tests use both dynamically allocated memory and std::vector to ensure flexibility
 * in input data structures.
 */

#include <gtest/gtest.h>
#include <vector>

// Declare C function with 'extern "C"' to prevent name mangling
extern "C" {
    #include "matrix_operations/linear_algebra.h"
}

// Test for the small-size matrix multiplication
TEST(MatrixMultiplicationTest, SmallMatrix) {
    double A[] = {
            1, 2,
            3, 4
    };
    double B[] = {
            5, 6
    };

    double y[2];

    double expected[] = {
            17,
            39
    };

    mat_vec_mult(A, B, y, 2);

    // Verify that each element matches the expected result
    for (int i = 0; i < 2; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }
}

TEST(MatrixMultiplicationTest, STLVectorMatrix) {

    const size_t N = 4;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0.0));
    std::vector<double>B (N, 1.0);
    std::vector<double>y (N, 0.0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i == j) ? 1.0 : 0.0;  // Set diagonal to 1, others to 0
        }
    }

    // Flatten the 2D matrix A into a 1D vector
    std::vector<double> A_flat(N * N, 0.0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A_flat[i * N + j] = A[i][j];
        }
    }

    std::vector<double>expected (N, 1.0);

    mat_vec_mult(A_flat.data(), B.data(), y.data(), N);

    // Verify that each element matches the expected result
    for (int i = 0; i < N; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }

}

// Test for the large-size matrix multiplication
TEST(MatrixMultiplicationTest, LargeMatrix) {
    const size_t N = 50000;

    auto* A = new double[N * N];
    auto* B = new double[N];
    auto* y = new double[N];
    auto* expected = new double[N];

    // Fill A with some values (Identity matrix)
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A[i * N + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Fill B with some values (All one)
    for (size_t i = 0; i < N; ++i) {
        B[i] = 1.0;
        expected[i] = 1.0;
    }

    mat_vec_mult(A, B, y, N);

    // Verify that each element matches the expected result
    for (size_t i = 0; i < N; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }

    // Free dynamically allocated memory
    delete[] A;
    delete[] B;
    delete[] y;
    delete[] expected;
}

// Test for the dot product of two vectors
TEST(MatrixDotProductTest, SmallVector) {

}

TEST(MatrixDotProductTest, LargeVector) {

}

// Test for the vector subtraction: result = a - b
TEST(MatrixSubtractionTest, SmallVector) {

}

TEST(MatrixSubtractionTest, LargeVector) {

}