//
// Created by QCZ on 10/2/2024.
//

#ifndef PROJECT_02_FVM_PRECONDITIONER_H
#define PROJECT_02_FVM_PRECONDITIONER_H

void precondition(const double* M, const double* r, double* z, int n);
void jacobi_precondition(const double* A, const double* r, double* z, int n);

#endif //PROJECT_02_FVM_PRECONDITIONER_H