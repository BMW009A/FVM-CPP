//
// Created by QCZ on 9/29/2024.
//

#include "HeatSolver.hpp"
#include <iostream>
#include "Grid.hpp"
#include "SimulationParameters.hpp"

using namespace std;

HeatSolver::HeatSolver(SimulationParameters &params, unique_ptr<TimeStepping> timeSteppingScheme)
    : params(params),
      T(params.N + 2, vector<double>(params.N + 2, params.TL)),
      Tp(params.N + 2, vector<double>(params.N + 2, params.TL)),
      To(params.N + 2, vector<double>(params.N + 2, params.TL)),
      grid(params.N, params.L, params.lm, params.rhoCp, params.dt),
      timeStepping(std::move(timeSteppingScheme)), convergence(params.crit, params.N) {}

void HeatSolver::initialize_temperature() {

    for (int j = 0; j < params.N + 2; ++j) {
        for (int i = 0; i < params.N + 2; ++i) {
            T[j][i] = params.TL;  // Apply the low temperature (300) at all the domain
        }
    }
    for (int i = 0; i < params.N + 2; ++i) {
        T[params.N + 1][i] = params.TH;  // Apply the high temperature at the top boundary
    }

}

void HeatSolver::run_simulation() {

    grid.initialize_coefficients();  // Initialize the coefficients of the grid
    initialize_temperature();  // Initialize the boundary condition

    for (int n = 0; n < params.NO; ++n) {
        timeStepping->step(T, To, grid, n, params.ST, Ts);

        if (convergence.check(T, Tp)) {
            cout << "Converged at time step " << n << endl;
            break;
        }

        timeStepping->update(To, T, params.N);
    }

    output.output_to_file(Ts, "computation_result.txt");

}