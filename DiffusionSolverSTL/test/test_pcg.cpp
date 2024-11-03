//
// Created by QCZ on 10/4/2024.
//
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "CPPVec2CArr.hpp"
// Declare C function with 'extern "C"' to prevent name mangling
extern "C" {
    #include "utils/PCG_solver.h"
}

using namespace std;

// Function to create the system of linear equations Ax = b, using central difference scheme
vector<vector<double>> CentralDiff(const size_t cols, const size_t rows) {

    vector<vector<double>> CenDiff(rows, vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (i - j == 1 || i - j == -1) {
                CenDiff[i][j] = -1;
            } else if (i == j) {
                CenDiff[i][j] = 2;
            } else {
                CenDiff[i][j] = 0;
            }
        }
    }

    return CenDiff;

}

// Function to create the system of linear equations Ax = b, using forward difference scheme
vector<vector<double>> ForwardDiff(const size_t cols, const size_t rows) {

    vector<vector<double>> ForDiff(rows, vector<double>(cols, 0.0));

    return ForDiff;

}

// Function to create the system of linear equations Ax = b, using Crank-Nicolson scheme
vector<vector<double>> CrankNDiff(const size_t cols, const size_t rows) {

    vector<vector<double>> CranDiff(rows, vector<double>(cols, 0.0));

    return CranDiff;

}

TEST(PCG_Test, smallSystem) {

    const size_t col = 10;
    const size_t row = 10;

    // Flatten 2D vector to a 1D C-style array using helper function 'Vector2Flatten'
    double* A = Vector2Flatten(CentralDiff(col, row));
    auto *x = new double[row]();
    auto *b = new double[row];
    auto *x_expect = new double[row];

    // Assign the values in x_expect
    for (size_t i = 0; i < row; ++i) {
        x_expect[i] = 1.0;
    }

    CRSMatrix smallMatrix;
    // Call the C function with the raw array
    if (dense_to_crs(A, row, col, &smallMatrix) != 0) {
        cerr << "Error converting dense matrix to CRS format.\n";
    }

    // Call PCG to solve the Ax = b
    if (pcg_solver(A, x, b, col, 1000, 0.01, "Jacobi") != 1) {
        cerr << "Error solving Ax = b.\n";
    } else {
        cout << "Finish the linear equations solving successful!" << endl;
    }

    // Verify that each element matches the expected result
    for (size_t i = 0; i < row; ++i) {
        EXPECT_DOUBLE_EQ(x[i], x_expect[i]);
    }

    // Free the dynamically allocated array after use
    delete[] A;
    delete[] x;
    delete[] b;
    delete[] x_expect;

}

TEST(PCG_Test, MediumSystem) {

}

TEST(PCG_Test, LargeSystem) {

}

TEST(PCG_Test, LoopSolve) {

}