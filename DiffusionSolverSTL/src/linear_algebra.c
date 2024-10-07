//
// Created by QCZ on 10/2/2024.
//

#include "linear_algebra.h"

// Matrix-vector multiplication: y = A * x
void mat_vec_mult(const double* A, const double* x, double* y, int n) {

    for (int i = 0; i < n; ++i) {
        y[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            y[i] += A[i * n + j] * x[j];
        }
    }

}

// Dot product of two vectors
double dot_product(const double* a, const double* b, int n) {

    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    return result;

}

// Vector subtraction: result = a - b
void vec_subtract(const double* a, const double* b, double* result, int n) {

    for (int i = 0; i < n; ++i) {
        result[i] = a[i] - b[i];
    }

}