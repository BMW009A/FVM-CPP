//
// Created by QCZ on 9/29/2024.
//

#include "ExplicitScheme.hpp"
#include <vector>

void ExplicitScheme::step(vector<vector<double>> &T, vector<vector<double>> &To, Grid &grid, int time_step_num,
                          int output_stride, vector<vector<vector<double>>> &Ts) {

    for (size_t j = 0; j < grid.N + 1; ++j) {
        for (size_t i = 0; i < grid.N + 1; ++i) {
            // Explicit time-stepping formula
            T[j][i] = (grid.ce[i] * To[j][i + 1] +
                       grid.cw[i] * To[j][i - 1] +
                       grid.cn[i] * To[j + 1][i] +
                       grid.cs[j] * To[j - 1][i] +
                       grid.co[j][i] - grid.ce[i] - grid.cw[i] - grid.cn[j] - grid.cs[j]) * To[j][i] / grid.co[j][i];
        }
    }

    // Call the inherited 'update' function to update the temperature field
    update(To, T, grid.N);

    if (time_step_num % output_stride == 0) {
        Ts.push_back(T);
    }

}