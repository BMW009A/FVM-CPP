//
// Created by QCZ on 10/1/2024.
//

#ifndef PROJECT_02_FVM_PCG_SOLVER_H
#define PROJECT_02_FVM_PCG_SOLVER_H

#ifdef __cpluscplus
extern "C" {
#endif

int pcg_solver(const double *A, const double *b, double *x, int n, int max_iter, double tol, const char* preconditioner_type);

#ifdef __cpluscplus
}
#endif

#endif //PROJECT_02_FVM_PCG_SOLVER_H