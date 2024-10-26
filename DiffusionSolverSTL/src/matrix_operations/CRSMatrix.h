//
// Created by QCZ on 10/24/2024.
//
// File: CRSMatrix.h

#ifndef PROJECT_02_FVM_CRSMATRIX_H
#define PROJECT_02_FVM_CRSMATRIX_H

#include <stddef.h>  // for size_t

typedef struct {
    double* values;  // None_zero values
    int* col_idx;    // Column indices of non-zero values
    int* row_ptr;    // Row pointers
    size_t nnz;      // Number of non-zero elements
    size_t rows;     // Number of row in the matrix
    size_t cols;     // Number of columns in the matrix
} CRSMatrix;

// Function to initialize CRS from dense matrix (C function)
void dense_to_crs(const double* dense, size_t rows, size_t cols, CRSMatrix* crs_matrix);

// Utility function to free the memory
void free_crs_matrix(CRSMatrix* matrix);

#endif //PROJECT_02_FVM_CRSMATRIX_H
