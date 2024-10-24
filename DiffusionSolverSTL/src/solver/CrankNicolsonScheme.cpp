//
// Created by QCZ on 9/29/2024.
//

#include "CrankNicolsonScheme.hpp"
#include <vector>
#include "utils/PCG_solver.h"

void CrankNicolsonScheme::step(vector<vector<double>> &T, vector<vector<double>> &To, Grid &grid, int time_step_num,
                          int output_stride, vector<vector<vector<double>>> &Ts) {

    // TODO: adding code for Crank-Nicolson Scheme


    // Call the inherited 'update' function to update the temperature field
    update(To, T, grid.N);

    if (time_step_num % output_stride == 0) {
        Ts.push_back(T);
    }

}