//
// Created by QCZ on 9/29/2024.
//
/*
 * File: ExplicitScheme.cpp
 * ------------------------
 * This file contains the implementation of the explicit scheme for the time-stepping
 * method in solving the diffusion equation. Explicit schemes are conditionally stable,
 * meaning they require small-time steps to maintain numerical stability.
 *
 * This implementation supports both 2D and 3D cases by overloading the 'step' function.
 * The 'step' function advances the solution to the next time step using the explicit
 * forward Euler method. For 2D and 3D cases, separate versions of the 'step' function
 * are provided to handle the different dimensionalities.
 */

#include "ExplicitScheme.hpp"
#include <vector>

/*
 * Function: step (2D)
 * -------------------
 * This function implements the explicit time-stepping scheme for 2D cases.
 * It advanced the temperature field 'T' by one time step based on the previous
 * temperature field 'To'. The new values are calculated using an explicit Euler method
 * for solving the heat equation.
 *
 * Parameters:
 * - T: The current temperature field (2D vector).
 * - To: The temperature field at the previous time step (2D vector).
 * - grid: The Grid object containing spatial discretization information.
 * - time_step_num: The current time step number.
 * - output_stride: Determines how often simulation results are written to the output.
 * - Ts: A 3D vector that stores temperature snapshots fot output.
 */
void ExplicitScheme::step(vector<vector<double>> &T, vector<vector<double>> &To, Grid &grid, int time_step_num,
                          int output_stride, vector<vector<vector<double>>> &Ts) {

    for (size_t j = 0; j < grid.N + 1; ++j) {
        for (size_t i = 0; i < grid.N + 1; ++i) {
            // Explicit time-stepping formula (2D case)
            T[j][i] = (grid.ce[i] * To[j][i + 1] +
                       grid.cw[i] * To[j][i - 1] +
                       grid.cn[i] * To[j + 1][i] +
                       grid.cs[j] * To[j - 1][i] +
                       grid.co2D[j][i] - grid.ce[i] - grid.cw[i] - grid.cn[j] - grid.cs[j]) * To[j][i] / grid.co2D[j][i];
        }
    }

    // Call the inherited 'update' function to update the temperature field
    update(To, T, grid.N);

    // Store temperature field in output if output_stride is met
    if (time_step_num % output_stride == 0) {
        Ts.push_back(T);
    }
}

/*
 * Function: step (3D)
 * -------------------
 * This function implements the explicit time-stepping scheme for 3D cases.
 * It advanced the temperature field 'T' by one time step based on the previous
 * temperature field 'To'. The new values are calculated using an explicit Euler method
 * for solving the heat equation.
 *
 * Parameters:
 * - T: The current temperature field (3D vector).
 * - To: The temperature field at the previous time step (3D vector).
 * - grid: The Grid object containing spatial discretization information.
 * - time_step_num: The current time step number.
 * - output_stride: Determines how often simulation results are written to the output.
 * - Ts: A 4D vector that stores temperature snapshots fot output.
 */
void ExplicitScheme::step(vector<vector<vector<double>>> &T, vector<vector<vector<double>>> &To, Grid &grid,
                          int time_step_num, int output_stride, vector<vector<vector<vector<double>>>> &Ts) {

    for (int k = 0; k < grid.N + 1; ++k) {
        for (int j = 0; j < grid.N + 1; ++j) {
            for (int i = 0; i < grid.N + 1; ++i) {
                // Explicit time-stepping formula (3D case)
                // (Dummy operation here, replace with actual formula for 3D)
                T[k][j][i] = 1.0;
            }
        }
    }

    // Call the inherited 'update' function to update the temperature field
    update(To, T, grid.N);

    // Store temperature field in output if output_stride is met
    if (time_step_num % output_stride == 0) {
        Ts.push_back(T);
    }
}