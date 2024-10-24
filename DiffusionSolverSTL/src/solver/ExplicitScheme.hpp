//
// Created by QCZ on 9/29/2024.
//
/*
 * File: ExplicitScheme.hpp
 * ------------------------
 * This file contains the definition of the ExplicitScheme class, which implements
 * the explicit time-stepping method for solving the diffusion equation in both 2D and 3D.
 *
 * Class Structure:
 * The ExplicitScheme class inherits from the base TimeStepping class and overrides
 * the 'step' method to implement the explicit time-stepping scheme. The explicit method
 * calculates the new temperature field based on the current field using a forward Euler approach.
 *
 * In explicit schemes, the new solution at the next time step is computed directly from the known values
 * at the current time step. However, explicit schemes require smaller time steps to maintain simulation stability.
 *
 * The class provides two overloaded 'step' methods:
 * - One for 2D grids (a 2D vector of doubles).
 * - One for 3D grids (a 3D vector of doubles).
 *
 * Dependencies:
 * This class depends on the "TimeStepping" base class and the "Grid" class for handling the
 * discretized spatial domain.
 *
 * Overridden Methods:
 * - step (2D): Implements the explicit scheme for 2D grids.
 * - step (3D): Implements the explicit scheme for 3D grids.
 */

#ifndef PROJECT_02_FVM_EXPLICITSCHEME_HPP
#define PROJECT_02_FVM_EXPLICITSCHEME_HPP

#include "TimeStepping.hpp"
#include "simulation_parameters/Grid.hpp"

/*
 * Class: ExplicitScheme
 * ---------------------
 * This class implements the explicit time-stepping method for solving the heat equation.
 * It provides separate implementations of the 'step' method for 2D and 3D simulation.
 */
class ExplicitScheme : public TimeStepping {
public:
    /*
     * Function: step (2D)
     * -------------------
     * Performs a time step using the explicit method for 2D grids.
     *
     * Parameters:
     * - T: The current temperature field (2D vector).
     * - To: The temperature field at the previous time step (2D vector).
     * - grid: The Grid object containing spatial discretization information.
     * - time_step_num: The current time step number.
     * - output_stride: Determines how often simulation results are written to the output.
     * - Ts: A 3D vector that stores temperature snapshots fot output.
     */
    void step(vector<vector<double>>& T, vector<vector<double>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<double>>>& Ts) override;

    /*
     * Function: step (3D)
     * -------------------
     * Performs a time step using the explicit method for 2D grids.
     *
     * Parameters:
     * - T: The current temperature field (3D vector).
     * - To: The temperature field at the previous time step (3D vector).
     * - grid: The Grid object containing spatial discretization information.
     * - time_step_num: The current time step number.
     * - output_stride: Determines how often simulation results are written to the output.
     * - Ts: A 4D vector that stores temperature snapshots fot output.
     */
    void step(vector<vector<vector<double>>>& T, vector<vector<vector<double>>>& To,
              Grid& grid, int time_step_num, int output_stride,
              vector<vector<vector<vector<double>>>>& Ts) override;

};

#endif //PROJECT_02_FVM_EXPLICITSCHEME_HPP