//
// Created by QCZ on 9/29/2024.
//

#include "HeatSolver.hpp"
#include <iostream>
#include "simulation_parameters/Grid.hpp"
#include "simulation_parameters/SimulationParameters.hpp"
#include "convergence/Convergence.hpp"
#include "IO/Output.hpp"

using namespace std;

HeatSolver::HeatSolver(SimulationParameters &params, unique_ptr<TimeStepping> timeSteppingScheme)
    : params(params),
      grid(params.N, params.L, params.lm, params.rhoCp, params.dt),
      timeStepping(std::move(timeSteppingScheme)),
      convergence(params.crit, params.max_iter, "convergence_log.txt", params),
      output("output.txt"){

    // Initialize 2D and 3D temperature fields size based on dimension
    if (params.dimension == 2) {
        T2D.resize(params.N + 2, vector<double>(params.N + 2, params.TL));
        Tp2D.resize(params.N + 2, vector<double>(params.N + 2, params.TL));
        To2D.resize(params.N + 2, vector<double>(params.N + 2, params.TL));
    } else if (params.dimension == 3) {
        T3D.resize(params.N + 2, vector<vector<double>>(params.N + 2, vector<double>(params.N + 2, params.TL)));
        Tp3D.resize(params.N + 2, vector<vector<double>>(params.N + 2, vector<double>(params.N + 2, params.TL)));
        To3D.resize(params.N + 2, vector<vector<double>>(params.N + 2, vector<double>(params.N + 2, params.TL)));
    }
}

// Function to initialize the temperature fields
void HeatSolver::initialization() {
    if (params.dimension == 2) {
        // For 2D initialization
        for (int j = 0; j < params.N + 2; ++j) {
            for (int i = 0; i < params.N + 2; ++i) {
                T2D[j][i] = params.TL;  // Apply the low temperature (300) at all the domain
            }
        }
        for (int i = 0; i < params.N + 2; ++i) {
            T2D[params.N + 1][i] = params.TH;  // Apply the high temperature at the top boundary
        }
    } else if (params.dimension == 3) {
        // For 3D initialization
        for (int k = 0; k < params.N + 2; ++k) {
            for (int j = 0; j < params.N + 2; ++j) {
                for (int i = 0; i < params.N + 2; ++i) {
                    T3D[k][j][i] = params.TL;  // Apply the low temperature (300) at all the domain
                }
            }
        }
        for (int j = 0; j < params.N + 2; ++j) {
            for (int i = 0; i < params.N + 2; ++i) {
                T3D[params.N + 1][j][i] = params.TH;  // Apply the high temperature at the top boundary
            }
        }
    }
}

void HeatSolver::run_simulation() {
    grid.initialize_coefficients();  // Initialize the coefficients of the grid
    initialization();  // Initialize the boundary condition

    if (params.dimension == 2) {
        run_2d_simulation();
    } else if (params.dimension == 3) {
        run_3d_simulation();
    }
}

void HeatSolver::run_2d_simulation() {
    for (int n = 0; n < params.NO; ++n) {
        timeStepping->step(T2D, To2D, grid, n, params.ST, Ts2D);

        if (convergence.check_convergence_2d(T2D)) {
            cout << "Converged at time step " << n << endl;
            break;
        }

        TimeStepping::update(To2D, T2D, params.N);
    }

    output.write_header({"Time ", "Temperature "});
}

void HeatSolver::run_3d_simulation() {
    for (int n = 0; n < params.NO; ++n) {
        timeStepping->step(T3D, To3D, grid, n, params.ST, Ts3D);

        if (convergence.check_convergence_3d(T3D)) {
            cout << "Converged at time step " << n << endl;
            break;
        }

        TimeStepping::update(To3D, T3D, params.N);
    }

    output.write_header({"Time ", "Temperature "});
}