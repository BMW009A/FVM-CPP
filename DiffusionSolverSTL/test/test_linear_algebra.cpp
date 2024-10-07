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
            5, 6,
            7, 8
    };

    double y[4];

    double expected[] = {
            19, 22,
            43, 50
    };

    mat_vec_mult(A, B, y, 4);

    // Verify that each element matches the expected result
    for (int i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }
}

// Test for the large-size matrix multiplication
TEST(MatrixMultiplicationTest, LargeMatrix) {
    const int N = 1000;
    double A[N * N];
    double B[N * N];
    double y[N * N] = {0.0};

    // Fill A and B with some values (Identity matrix)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = (i == j) ? 1.0 : 0.0;
            B[i * N + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    double expected[N * N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            expected[i * N + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    mat_vec_mult(A, B, y, N);

    // Verify that each element matches the expected result
    for (int i = 0; i < N; ++i) {
        EXPECT_DOUBLE_EQ(y[i], expected[i]);
    }
}