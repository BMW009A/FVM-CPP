//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_HEATSOLVER_HPP
#define PROJECT_02_FVM_HEATSOLVER_HPP

#include <vector>
#include <memory>
#include "Grid.hpp"
#include "TimeStepping.hpp"
#include "SimulationParameters.hpp"
#include "Convergence.hpp"
#include "Output.hpp"

using namespace std;

class HeatSolver {
public:
    HeatSolver(SimulationParameters& params, unique_ptr<TimeStepping> timeSteppingScheme);

    void run_simulation();

private:
    SimulationParameters& params;  // Reference to simulation parameters
    Grid grid;
    unique_ptr<TimeStepping> timeStepping;
    Convergence convergence;
    Output output;

    // Data structures for 2D and 3D temperature fields
    vector<vector<double>> T2D, Tp2D, To2D;
    vector<vector<vector<double>>> T3D, Tp3D, To3D;
    vector<vector<vector<double>>> Ts2D;
    vector<vector<vector<vector<double>>>> Ts3D;

    // Initialize temperature fields based on dimensionality
    void initialization();

    // Method to run 2D and 3D simulations
    void run_2d_simulation();
    void run_3d_simulation();

};

#endif //PROJECT_02_FVM_HEATSOLVER_HPP