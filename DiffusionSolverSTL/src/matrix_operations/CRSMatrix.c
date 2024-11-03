//
// Created by QCZ on 10/24/2024.
//

/*
 * File: CRSMatrix.c
 * -----------------
 * This file contains the implementation of the CRS (Compressed Row Storage) matrix format
 * and provides functions to convert a sparse matrix to CRS format and free the allocated memory
 *
 * The CRS format is efficient for storing sparse matrices, as it only stores non-zero elements
 * and reduces memory usage and computational time in matrix operations.
 *
 * Functions:
 *  - dense_to_crs: Converts a dense matrix to a CRS matrix format.
 *  - free_crs_matrix: Frees memory allocated for the CRS matrix.
 */

#include "CRSMatrix.h"
#include "CPPVec2CArr.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <omp_llvm.h>

/*
 * Function: dense_to_crs
 * ----------------------
 * Converts a dense matrix to Compressed Row Storage (CRS) format.
 *
 * Parameters:
 *
 */
int dense_to_crs(const double* dense, size_t rows, size_t cols, CRSMatrix* crs_matrix) {

    // Check the inputs validation
    if (!dense || !crs_matrix || rows == 0 || cols ==0) {
        fprintf(stderr, "Invalid input to dense_to_crs.\n");
        return -1;  // Error code for invalid input
    }

    // Count non-zero elements (nnz)
    size_t nnz = 0;
    #pragma omp parallel for reduction(+:nnz)
    for (size_t i = 0; i < rows * cols; ++i) {
        if (dense[i] != 0.0) {
            nnz++;
        }
    }

    // Allocate memory for CRS arrays, with error checking
    crs_matrix->values = (double*) calloc(nnz, sizeof(double));
    crs_matrix->col_idx = (size_t*) calloc(nnz, sizeof(size_t));
    crs_matrix->row_ptr = (size_t*) calloc(rows + 1, sizeof(size_t));

    if (!crs_matrix->values || !crs_matrix->col_idx || !crs_matrix->row_ptr) {
        fprintf(stderr, "Memory allocation failed in dense_to_crs.\n");
        free_crs_matrix(crs_matrix);
        return -1;
    }

    crs_matrix->rows = rows;
    crs_matrix->cols = cols;

    // Fill CRS arrays
    int k = 0;
    #pragma omp parallel for shared(k)
    for (int i = 0; i < rows; ++i) {
        size_t row_start = k;
        for (int j = 0; j < cols; ++j) {
            if (dense[i * cols + j] != 0.0) {
                #pragma omp critical
                {
                    crs_matrix->values[k] = dense[i * cols + j];
                    crs_matrix->col_idx[k] = j;
                    k++;
                }
            }
        }
        crs_matrix->row_ptr[i] =  row_start;
    }
    crs_matrix->row_ptr[rows] = k;  // Final element in row_ptr

    return 0;

}

/*
 * Function: free_crs_matrix
 * -------------------------
 * Frees the memory allocated for a CRS matrix.
 *
 * Parameters:
 *   matrix - Pointer to the CRSMatrix structure to be freed.
 *
 * This function releases the memory allocated for the values, column indices, and row
 * pointers of the CRS matrix and sets the pointers to NULL to avoid dangling references.
 */
void free_crs_matrix(CRSMatrix* matrix) {
    if (matrix->values) free(matrix->values);
    if (matrix->col_idx) free(matrix->col_idx);
    if (matrix->row_ptr) free(matrix->row_ptr);

    matrix->row_ptr = NULL;
    matrix->col_idx = NULL;
    matrix->values = NULL;
}