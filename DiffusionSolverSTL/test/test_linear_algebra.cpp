//
// Created by QCZ on 10/4/2024.
//

#include <gtest/gtest.h>

// Declare C function with 'extern "C"' to prevent name mangling
extern "C" {
    #include "linear_algebra.h"
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

// Test for the large-size matrix multiplication
TEST(MatrixMultiplicationTest, LargeMatrix) {
    const int N = 10000;

    auto* A = new double[N * N];
    auto* B = new double[N];
    auto* y = new double[N];
    auto* expected = new double[N];

    // Fill A with some values (Identity matrix)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Fill B with some values (All one)
    for (int i = 0; i < N; ++i) {
        B[i] = 1.0;
        expected[i] = 1.0;
    }

    mat_vec_mult(A, B, y, N);

    // Verify that each element matches the expected result
    for (int i = 0; i < N; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }

    // Free dynamically allocated memory
    delete[] A;
    delete[] B;
    delete[] y;
    delete[] expected;
}