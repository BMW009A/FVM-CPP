//
// Created by QCZ on 9/29/2024.
//
/*
 * File: TimeStepping.hpp
 * ----------------------
 * This file defines the abstract base class 'TimeStepping', which provides the interface
 * for time-stepping schemes used in solving the diffusion equation. Derived classes must
 * implement the 'step' function, which is overloaded for both 2D and 3D cases.
 *
 * The 'update' function is shared by all derived classes and is responsible for updating
 * the temperature field from one time step to the next.
 */

#ifndef PROJECT_02_FVM_TIMESTEPPING_HPP
#define PROJECT_02_FVM_TIMESTEPPING_HPP

#include <vector>
#include "Grid.hpp"

using namespace std;

class TimeStepping {
public:
    virtual ~TimeStepping() = default;

    /*
     * Pure virtual function: step (2D)
     * --------------------------------
     * Advances the temperature field 'T' to the next time step in 2D simulations.
     * This function must be implemented by any derived class, which defines the
     * specific time-stepping scheme (Explicit, Implicit, CrankNicolson)
     *
     * Parameters:
     * - T: The current temperature field (2D vector).
     * - To: The temperature field at the previous time step (2D vector).
     * - grid: The Grid object containing spatial discretization information.
     * - time_step_num: The current time step number.
     * - output_stride: Determines how often simulation results are written to the output.
     * - Ts: A 3D vector that stores temperature snapshots fot output.
     */
    virtual void step(vector<vector<double>>& T, vector<vector<double>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<double>>>& Ts) = 0;
    /*
     * Pure virtual function: step (2D)
     * --------------------------------
     * Advances the temperature field 'T' to the next time step in 2D simulations.
     * This function must be implemented by any derived class, which defines the
     * specific time-stepping scheme (Explicit, Implicit, CrankNicolson)
     *
     * Parameters:
     * - T: The current temperature field (2D vector).
     * - To: The temperature field at the previous time step (2D vector).
     * - grid: The Grid object containing spatial discretization information.
     * - time_step_num: The current time step number.
     * - output_stride: Determines how often simulation results are written to the output.
     * - Ts: A 3D vector that stores temperature snapshots fot output.
     */
    virtual void step(vector<vector<vector<double>>>& T, vector<vector<vector<double>>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<vector<double>>>>& Ts) = 0;

    /*
     * Function: update (2D)
     * ---------------------
     * Updates the previous temperature field 'To' with the current field 'T' for 2D simulations.
     * This function is used to prepare for the next time step by storing the Latest results.
     *
     * Parameters:
     * - To: The temperature field from the previous time step (will be updated).
     * - T: The temperature field at the current time step.
     * - N: The number of grid points in one dimension (excluding boundaries).
     */
    static void update(vector<vector<double>>& To, const vector<vector<double>>& T, int N);

    /*
     * Function: update (2D)
     * ---------------------
     * Updates the previous temperature field 'To' with the current field 'T' for 2D simulations.
     * This function is used to prepare for the next time step by storing the Latest results.
     *
     * Parameters:
     * - To: The temperature field from the previous time step (will be updated).
     * - T: The temperature field at the current time step.
     * - N: The number of grid points in one dimension (excluding boundaries).
     */
    static void update(vector<vector<vector<double>>>& To, const vector<vector<vector<double>>>& T, int N);

};

#endif //PROJECT_02_FVM_TIMESTEPPING_HPP