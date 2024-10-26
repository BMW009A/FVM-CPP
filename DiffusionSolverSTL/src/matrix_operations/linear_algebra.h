//
// Created by QCZ on 10/2/2024.
//

#ifndef PROJECT_02_FVM_LINEAR_ALGEBRA_H
#define PROJECT_02_FVM_LINEAR_ALGEBRA_H


#include "CRSMatrix.h"

int mat_vec_mult(const double* A, const double* x, double* y, int n);
int crs_mat_vec_mult(const CRSMatrix* A, const double* x, double* y);
double dot_product(const double* a, const double* b, int n);
void vec_subtract(const double* a, const double* b, double* result, int n);

#endif //PROJECT_02_FVM_LINEAR_ALGEBRA_H