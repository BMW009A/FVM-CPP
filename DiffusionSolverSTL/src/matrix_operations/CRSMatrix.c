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

    // Step 1 Count the number of non-zero elements (nnz)
    size_t nnz = 0;
    #pragma omp parallel for reduction(+:nnz)
    for (size_t i = 0; i < rows * cols; ++i) {
        if (dense[i] != 0.0) {
            nnz++;
        }
    }

    // Allocate memory for CRS arrays
    crs_matrix->values = (double*) malloc(nnz * sizeof(double));
    crs_matrix->col_idx = (size_t*) malloc(nnz * sizeof(size_t));
    crs_matrix->row_ptr = (size_t*) malloc((nnz + 1) * sizeof(size_t));
    if (!crs_matrix->values || !crs_matrix->col_idx || !crs_matrix->row_ptr) {
        fprintf(stderr, "Memory allocation failed in dense_to_crs.\n");
        return -1;
    }

    crs_matrix->rows = rows;
    crs_matrix->cols = cols;

    // Step 2: Allocate thread-private workspaces
    size_t* thread_row_starts = (size_t*) malloc((omp_get_max_threads() + 1) * sizeof(size_t));
    if (!thread_row_starts) {
        fprintf(stderr, "Memory allocation for thread-private workspaces failed.\n");
        free_crs_matrix(crs_matrix);
        return -1;
    }
    thread_row_starts[0] = 0;

    // Step 3: Divide rows among threads and compute local nnz
    int memory_error = 0;
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        size_t start_row = (rows * thread_id) / num_threads;
        size_t end_row = (rows * (thread_id + 1)) / num_threads;

        size_t local_nnz = 0;

        // Count non-zero elements in thread's portion
        for (size_t i = start_row; i < end_row; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (dense[i * cols + j] != 0.0) {
                    local_nnz++;
                }
            }
        }

        thread_row_starts[thread_id + 1] = local_nnz;

        #pragma omp barrier
        #pragma omp single
        {
            // Compute prefix sum of thread-local nnz counts
            for (int t = 0; t <= num_threads; ++t) {
                thread_row_starts[t] += thread_row_starts[t - 1];
            }
        }

        // Allocate row_ptr_local with proper size
        size_t* row_ptr_local = (size_t*) malloc((end_row - start_row + 1) * sizeof(size_t));

        // Handle potential null pointer for row_ptr_local
        if (!row_ptr_local) {
            #pragma omp critical
            {
                fprintf(stderr, "Thread %d failed to allocate memory for row_ptr_local. Exiting thread.\n", omp_get_thread_num());
                memory_error = 1;  // Signal memory allocation failure
            }
            #pragma omp cancel parallel   //Stop all threads in the parallel region
        }
        
        // Step 4: Populate thread_local CRS arrays
        size_t k = thread_row_starts[thread_id];
        for (size_t i = start_row; i < end_row; ++i) {
            size_t local_index = i - start_row;  // Compute local index
            if (local_index >= (end_row - start_row + 1)) {
                #pragma omp critical
                {
                    fprintf(stderr, "Thread %d detected out-of-bounds access in row_ptr_local.\n", omp_get_thread_num());
                }
                memory_error = 1;
                #pragma omp cancel parallel   //Stop all threads in the parallel region
            }

            row_ptr_local[i - start_row] = k;  // Thread-local row_ptr entry
            for (size_t j = 0; j < cols; ++j) {
                if (dense[i * cols + j] != 0.0) {
                    crs_matrix->values[k] = dense[i * cols +j];
                    crs_matrix->col_idx[k] = j;
                    k++;
                }
            }
        }

        // Final entry for this thread's row_ptr
        size_t final_index = end_row - start_row;
        if (final_index >= (end_row - start_row + 1)) {
            #pragma omp critical
            {
                fprintf(stderr, "Thread %d detected out-of-bounds access in row_ptr_local final entry.\n", omp_get_thread_num());
            }
            memory_error = 1;
            #pragma omp cancel parallel   //Stop all threads in the parallel region
        }

        row_ptr_local[end_row - start_row] = k;  // Final row_ptr entry for this thread

        // Step 5: Aggregate results into global CRS arrays
        #pragma omp critical
        {
            if (!memory_error) {
                size_t rows_processed = end_row - start_row;
                for (size_t r = 0; r <= rows_processed ; ++r) {
                    crs_matrix->row_ptr[start_row + r] = row_ptr_local[r];
                }
            }

        }

        free(row_ptr_local);  // Ensure row_ptr_local is freed

    }

    if (memory_error) {
        fprintf(stderr, "Memory allocation failed in one of the threads.\n");
        free(thread_row_starts);
        free_crs_matrix(crs_matrix);
        return -1;
    }

    // Step 6: Finalize global row_ptr
    crs_matrix->row_ptr[rows] = thread_row_starts[omp_get_max_threads()];
    free(thread_row_starts);

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
    if (!matrix) return;  // Handle null pointer
    if (matrix->values) free(matrix->values);
    if (matrix->col_idx) free(matrix->col_idx);
    if (matrix->row_ptr) free(matrix->row_ptr);

    matrix->row_ptr = NULL;
    matrix->col_idx = NULL;
    matrix->values = NULL;
}