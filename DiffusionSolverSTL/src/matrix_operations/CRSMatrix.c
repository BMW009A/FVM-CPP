//
// Created by QCZ on 10/24/2024.
//
// File: CRSMatrix.c

#include "CRSMatrix.h"
#include <stdlib.h>
#include <stdio.h>

void dense_to_crs(const double* dense, size_t rows, size_t cols, CRSMatrix* crs_matrix) {

    // Count non-zero elements (nnz)
    size_t nnz = 0;
    for (size_t i = 0; i < rows * cols; ++i) {
        if (dense[i] != 0.0) {
            nnz++;
        }
    }

    // Allocate memory for CRS arrays
    crs_matrix->values = (double*) malloc(nnz * sizeof(double));
    crs_matrix->col_idx = (int*) malloc(nnz * sizeof(int));
    crs_matrix->row_ptr = (int*) malloc((rows + 1) * sizeof(int));
    crs_matrix->rows = rows;
    crs_matrix->cols = cols;

    // Fill CRS arrays
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        crs_matrix->row_ptr[i] = k;
        for (int j = 0; j < cols; ++j) {
            if (dense[i * cols + j] != 0.0) {
                crs_matrix->values[k] = dense[i * cols + j];
                crs_matrix->col_idx[k] = j;
                k++;
            }
        }
    }
    crs_matrix->row_ptr[rows] = k;  // Final element in row_ptr
}