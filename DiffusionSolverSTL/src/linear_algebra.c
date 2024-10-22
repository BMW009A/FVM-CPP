//
// Created by QCZ on 10/2/2024.
//

#include "linear_algebra.h"
#include "stdio.h"
#include "omp.h"

// Define a threshold for parallel computation (Should be tune for better performance according different systems/hardwares)
const int PARALLEL_THRESHOLD = 1000;

/*
 * Function: mat_vec_mult
 * ----------------------
 * This function performs matrix-vector multiplications: y = A * x.
 *
 * Inputs:
 *   - A: Pointer to matrix A (1D array, flattened(if using std::vector or Eigen::VectorX))
 *   - B: Pointer to vector x
 *   - y: Pointer to output vector y
 *   - n: Size of the matrix and vectors (n*n matrix and size n vectors)
 *
 * Returns:
 *   - 0 on success
 *   - -1 on error
 *
 * Error handling:
 *   - Checks for null pointers (A, x, or y) and returns an error if found.
 *   - Verifies that the matrix dimension (n) is positive.
 */
int mat_vec_mult(const double* A, const double* x, double* y, int n) {

    // Error handling: check if matrix and vectors are valid
    if (A == NULL || x == NULL || y == NULL) {
        fprintf(stderr, "Error: Null pointer passed to mat_vec_mult.\n");
        return -1;  // Return error code
    }

    if (n <= 0) {
        fprintf(stderr, "Error: Matrix dimension must be positive.\n");
        return -1;  // Return error code
    }

    // Check if the matrix size exceeds the threshold for parallelization
    if (n >= PARALLEL_THRESHOLD) {
        printf("Parallel computation used for matrix-vector multiplication\n");

        // Parallel matrix-vector multiplication
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            y[i] = 0.0;
            for (int j = 0; j < n; ++j) {
                y[i] += A[i * n + j] * x[j];
            }
        }
    } else {
        printf("Serial computation used for matrix-vector multiplication\n");
        // Serial matrix-vector multiplication
        for (int i = 0; i < n; ++i) {   // Initialization for the y vector.
            y[i] = 0.0;
        }

        // Perform matrix-vector multiplication
        if (n == 1) {
            y[0] = A[0] * x[0];
        } else {
            for (int i = 0; i < n; ++i) {
                y[i] = 0.0;
                for (int j = 0; j < n; ++j) {
                    y[i] += A[i * n + j] * x[j];
                }
            }
        }
    }

    return 0;  // Return success code
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