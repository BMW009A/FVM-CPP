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
    vector<vector<double>> T, Tp, To;
    vector<vector<vector<double>>> Ts;

    Grid grid;
    unique_ptr<TimeStepping> timeStepping;
    Convergence convergence;
    Output output;

    void initialize_temperature();

};












#endif //PROJECT_02_FVM_HEATSOLVER_HPP
