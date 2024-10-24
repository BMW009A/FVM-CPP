//
// Created by QCZ on 10/2/2024.
//
/*
 * File: preconditioner.c
 * ----------------------
 * This program is source code of three different preconditioners: default, Jacobi and Incomplete Cholesky.
 * The default preconditioner is using an identity matrix as preconditioner matrix.
 * Jacobi preconditioner is dividing residual by the diagonal element of matrix A.
 * Incomplete Cholesky preconditioner
 *
 */

#include "preconditioner.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

void precondition(const double* M, const double* r, double* z, int n) {

    for (int i = 0; i < n; ++i) {
        z[i] = r[i];   // M is identity matrix, M * z = r --> z = M^(-1) * r = r
    }

}

void jacobi_precondition(const double* A, const double* r, double* z, int n) {

    for (int i = 0; i < n; ++i) {
        z[i] = r[i] / A[i * n + i];  // Divide residual by the diagonal element of A
    }

}

// Function to compute the Incomplete Cholesky factorization of matrix A
void incomplete_cholesky(const double* A, double* L, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double sum = A[i * n +j];

            for (int k = 0; k < j; ++k) {
                sum -= L[i * n + k] * L[j * n + k];
            }

            if (i == j) {
                // Diagonal element
                if (sum <= 0.0) {
                    printf("Matrix is not positive definite.\n");
                    return;
                }
                L[i * n + i] = sqrt(sum);
            } else {
                // Off-diagonal element
                L[i * n + j] = sum / L[j * n + j];
            }
        }
    }
}

// Apply Incomplete Cholesky preconditioner: solve M * z = r, where M ≈ A
void ic_precondition(const double* L, const double* r, double* z, int n) {

    double* y = (double*) malloc(n * sizeof(double ));

    // Solve L * y = r (forward substitution)
    for (int i = 0; i < n; ++i) {
        double sum = r[i];
        for (int j = 0; j < i; ++j) {
            sum -= L[i * n + j] * y[j];
        }
        y[i] = sum / L[i * n + i];
    }

    // Solve L^T * z = y (backward substitution)
    for (int i = n - 1; i >= 0; --i) {
        double sum = y[i];
        for (int j = i + 1; j < n; ++j) {
            sum -= L[j * n + i] * z[j];
        }
        z[i] = sum / L[i * n + i];
    }

    free(y);

}