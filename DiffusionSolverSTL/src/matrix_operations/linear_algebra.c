//
// Created by QCZ on 10/2/2024.
//

#include "linear_algebra.h"
#include "stdio.h"
#include <omp_llvm.h>
// Define a threshold for parallel computation (Should be tune for better performance according different systems/hardware)
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

//    if (n == 1) {
//        y[0] = A[0] * x[0];
//    } else {
//        for (int i = 0; i < n; ++i) {
//            y[i] = 0.0;
//            for (int j = 0; j < n; ++j) {
//                y[i] += A[i * n + j] * x[j];
//            }
//        }
//    }

    // Set the number of threads
    omp_set_num_threads(omp_get_max_threads());  // Set the number of threads to 4
    // Optimal block size may vary based on hardware
    int block_size = 128;

    long long i;
    for (i = 0; i < n; ++i) {
        y[i] = 0.0;
    }

    // Check if the matrix size exceeds the threshold for parallelization
    if (n >= PARALLEL_THRESHOLD) {
        printf("Parallel computation used for matrix-vector multiplication with %d threads.\n", 32);
        // Parallel matrix-vector multiplication

                #pragma omp parallel for schedule(static)
                    for (i = 0; i < n; i += block_size) {
                        for (long long j = 0; j < n; j += block_size) {
                            for (long long ii = i; ii < i + block_size && ii < n; ++ii) {
                                for (long long jj = j; jj < j + block_size && jj < n; ++jj) {
                                    y[ii] += A[ii * n + jj] * x[jj];
                                }
                            }
                        }
                    }

    } else {
        printf("Serial computation used for matrix-vector multiplication\n");
        // Serial matrix-vector multiplication
//        for (i = 0; i < n; ++i) {   // Initialization for the y vector (Done before if)
//            y[i] = 0.0;
//        }

        // Perform matrix-vector multiplication
        for (i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                y[i] += A[i * n + j] * x[j];
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