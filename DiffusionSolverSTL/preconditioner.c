//
// Created by QCZ on 10/2/2024.
//

#include "preconditioner.h"

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

void incomplete_cholesky(const double* A, double* L, int n) {


}

void ic_precondition(const double* L, const double* r, double* z, int n) {


}