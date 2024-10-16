//
// Created by QCZ on 10/1/2024.
//
/*
 * File: PCG_solver.c
 * ------------------
 * This file is source code of Pre-Condition Conjugate Gradient iterative method,
 * which is use for solving the linear system Ax = b.
 *
 * Main Algorithm Steps:
 * 1. r0 = b - A * x0, where x0 is approximate initial solution or 0s vector, and r0 is initial residual, if r0 is
 *    sufficiently small, then return x0 as the result;
 * 2. p0 = r0 and k = 0;
 * 3. Repeat until convergence or maximum iterations are reached:
 *           - alpha_k = dot(rk, rk) / dot(pk, A * pk);
 *           - x_k+1 = x_k + alpha_k * pk;
 *           - r_k+1 = r_k - alpha_k * A * pk; (if r_k+1 is sufficiently small, then next loop)
 *           - beta_k = dot(r_k+1, r_k+1) / dot(rk, rk);
 *           - p_k+1 = r_k+1 + beta_k * p_k;
 *           - k += 1;
 * 4. If convergence is achieved, return the solution x_k+1.
 *    Otherwise, return failure after max iterations.
 *
 * The code also supports different preconditioners, such as:
 *  - Jacobi
 *  - Incomplete Cholesky
 *  - Identity (Default, preconditioner)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "PCG_solver.h"
#include "linear_algebra.h"
#include "preconditioner.h"

int pcg_solver(const double *A, const double *b, double *x, int n, int max_iter, double tol, const char* preconditioner_type) {

    /*
     * Function: pcg_solver
     * --------------------
     * Solve the linear system Ax = b using the Preconditioned Conjugate Gradient method.
     * Parameters:
     *  - A: Pointer to matrix A (1D row-major array)
     *  - b: Pointer to vector b (right-hand side)
     *  - x: Pointer to the initial guess vector x (also stores the solution)
     *  - n: Number of rows/columns in A
     *  - max_iter: Maximum number of iterations
     *  - tol: Convergence tolerance
     *  preconditioner_type: Type of preconditioner ("Jacobi", "IncompleteCholesky", or "Default")
     * Returns:
     *  -0 if converged, 1 otherwise (max iterations reached without convergence)
     */

    // Allocate memory for the vector
    double* r = (double*) malloc(n * sizeof(double ));
    double* z = (double*) malloc(n * sizeof(double ));
    double* p = (double*) malloc(n * sizeof(double ));
    double* Ap = (double*) malloc(n * sizeof(double ));

    // Compute initial residual: r = b - A * x
    mat_vec_mult(A, x, r, n);  // y = A * x, return
    vec_subtract(b, r, r, n);  // in this case, initialize the first residual as r,
                                          // using r as the intermeddle variable to pass the result from vector multiply.

    // Preconditioning step, choose different preconditioner
    if (strcmp(preconditioner_type, "Jacobi") == 0) {
        jacobi_precondition(A, r, z, n);
    } else if (strcmp(preconditioner_type, "incomplete_cholesky") == 0) {
        double* L = (double*) malloc(n * n * sizeof(double ));
        incomplete_cholesky(A, L, n);
        ic_precondition(L, r, z, n);
        free(L);
    } else {
        precondition(A, r, z, n);  // Default to identity (no preconditioner)
    }

    // Set initial search direction p = z
    for (int i = 0; i < n; ++i) {
        p[i] = z[i];
    }
    
    double r_dot_z_old = dot_product(r, z, n);

    // Iterative loop
    for (int i = 0; i < max_iter; ++i) {

        // do A * pk
        mat_vec_mult(A, p, Ap, n);

        // alpha_k = dot(rk, rk) / dot(pk, A * pk);
        double alpha = r_dot_z_old / dot_product(p, Ap, n);

        // Update solution x : x_k+1 = x_k + alpha_k * pk
        for (int j = 0; j < n; ++j) {
            x[j] += alpha * p[j];
        }

        // Update residual r : r_k+1 = r_k - alpha_k * A * pk
        for (int j = 0; j < n; ++j) {
            r[j] -= alpha * Ap[j];
        }

        // Check for the convergence
        double r_norm = sqrt(dot_product(r, r, n));
        if (r_norm < tol) {
            printf("PCG converged after %d iterations\n", i + 1);
            free(r); free(z); free(p); free(Ap);
            return 0;
        }

        // Preconditioning step
        if (strcmp(preconditioner_type, "Jacobi") == 0) {
            jacobi_precondition(A, r, z, n);
        } else if (strcmp(preconditioner_type, "IncompleteCholesky") == 0) {
            double* L = (double*)malloc(n * n * sizeof(double));
            incomplete_cholesky(A, L, n);
            ic_precondition(L, r, z, n);
            free(L);
        } else {
            precondition(A, r, z, n);  // Default to identity
        }

        double r_dot_new = dot_product(r, z, n);

        // beta_k = dot(r_k+1, r_k+1) / dot(rk, rk);
        double beta = r_dot_new / r_dot_z_old;

        // p_k+1 = r_k+1 + beta_k * p_k;
        for (int j = 0; j < n; ++j) {
            p[j] = z[j] + beta * p[j];
        }

        r_dot_z_old = r_dot_new;  //Update for next iteration

    }

    // If we reach this point, the algorithm did not converge within max_iter
    printf("PCG did not converge after %d iterations\n", max_iter);
    free(r); free(z); free(p); free(Ap);
    return 1;
}