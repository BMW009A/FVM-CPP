//
// Created by QCZ on 9/29/2024.
//
#include <iostream>
#include <unordered_map>
#include "solver/HeatSolver.hpp"
#include "solver/ExplicitScheme.hpp"
#include "solver/ImplicitScheme.hpp"
#include "solver/CrankNicolsonScheme.hpp"
#include "simulation_parameters/SimulationParameters.hpp"
#include "solver/SchemeType.hpp"
#include "IO/ConfigParser.hpp"

using namespace std;

int main() {

    ConfigParser parser;
// Variables to store the values read from the file
    int dimension{};       // 2 for 2D, 3 for 3D
    double L{};            // Length of the cavity [m]
    int N{};               // Number of grid points
    double TL{};           // Low temperature [K]
    double TH{};           // High temperature [K]
    double crit{};         // Convergence criterion
    int max_iter{};      // Maximum iteration
    int NO{};              // Number of time steps
    int ST{};              // Output stride
    double lm{};           // Thermal conductivity [W/mK]
    double rhoCp{};        // Volumetric specific heat [J/m3K]
    double alpha{};      // Thermal diffusivity [m²/s]
    double a{};          // heat diffusivity [m2/s]
    double density{};    // density
    double r{};          // diffusion number < 1/4 for 2D stability
    double dt{};         // dt CFL [s]
    double dl{};         // Grid spacing [m]
    double relax_factor{}; // relax factor
    string Solver_type{};  // Solver type for temporal discretization
    string Linear_solver_type{};  // Linear solver type for linear algebra systems
    double Solver_tolerance{};   // Tolerance for convergence for linear algebra systems
    string Preconditioner_type{};   // Preconditioner type

    unordered_map inputs = parser.read_config(R"(C:\Users\QCZ\CLionProjects\Project-02-FVM\DiffusionSolverSTL\config\config.txt)");

    for (const auto& pair: inputs) {
        if (pair.first == "Dimension") {
            dimension = stoi(pair.second);  // 2 for 2D, 3 for 3D
        } else if (pair.first == "Time_steps") {
            NO = stoi(pair.second);  // Number of time steps
        } else if (pair.first == "Output_stride") {
            ST = stoi(pair.second);  // How often the output is written (frequency)
        } else if (pair.first == "Length_x" || pair.first == "Length_y" || pair.first == "Length_z") {
            L = stod(pair.second);  // Length of the domain in x, y, or z direction [m]
        } else if (pair.first == "N_x" || pair.first == "N_y" || pair.first == "N_z") {
            N = stoi(pair.second);  // Number of grid points in x, y, or z direction
        } else if (pair.first == "Thermal_conductivity") {
            lm = stod(pair.second);  // Thermal conductivity [W/mK]
        } else if (pair.first == "Density") {
            density = stod(pair.second);  // Density of the material [kg/m^3]
        } else if (pair.first == "Specific_heat") {
            rhoCp = stod(pair.second);  // Specific heat capacity [J/kgK]
        } else if (pair.first == "Temperature_low") {
            TL = stod(pair.second);  // Low temperature boundary [K]
        } else if (pair.first == "Temperature_high") {
            TH = stod(pair.second);  // High temperature boundary [K]
        } else if (pair.first == "Convergence_criterion") {
            crit = stod(pair.second);  // Convergence tolerance for iterative solvers
        } else if (pair.first == "Solver_type") {
            Solver_type = pair.second;  // Time-stepping scheme (Explicit, Implicit, etc.)
        } else if (pair.first == "Relaxation_factor") {
            relax_factor = stod(pair.second);  // Relaxation factor for iterative solvers
        } else if (pair.first == "Linear_solver_type") {
            Linear_solver_type = pair.second;  // Linear solver method (e.g., PCG, Gauss-Seidel)
        } else if (pair.first == "Max_iterations") {
            max_iter = stoi(pair.second);  // Maximum number of iterations for the solver
        } else if (pair.first == "Solver_tolerance") {
            Solver_tolerance = stod(pair.second);  // Tolerance for solver convergence
        } else if (pair.first == "Preconditioner_type") {
            Preconditioner_type = pair.second;  // Preconditioner type (None, Jacobi, Incomplete Cholesky)
        }
    }

    // Validate parameters read from 'config.txt'
    parser.validate_config(inputs);

    // Output parameters read from 'config.txt' to console
    parser.output_config(inputs);

    // Set up simulation parameters
    SimulationParameters params(L, N, TL, TH, crit, NO, ST, dl, lm, density, alpha);

    // Instantiate the appropriate time-stepping scheme
    std::unique_ptr<TimeStepping> timeStepScheme;

    // Select the time-stepping scheme
    if (Solver_type == "Explicit") {
        timeStepScheme = std::make_unique<ExplicitScheme>();
    } else if (Solver_type == "Implicit") {
        timeStepScheme = std::make_unique<ImplicitScheme>();
    } else if (Solver_type == "CrankNicolson") {
        timeStepScheme = std::make_unique<CrankNicolsonScheme>();
    } else {
        cerr << "Error: Unsupported solver type ' " << Solver_type << " '." << endl;
        return -1;
    }

//    // Create the solver and pass the time-stepping scheme
//    HeatSolver solver(params, std::move(timeStepScheme));
//    solver.run_simulation();

}