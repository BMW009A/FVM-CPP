//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_SIMULATIONPARAMETERS_HPP
#define PROJECT_02_FVM_SIMULATIONPARAMETERS_HPP

#include "Grid.hpp"

class SimulationParameters {
public:
    // Constructor to initialize all parameters
    SimulationParameters(double L, int N, double TL, double TH, double crit, int NO, int ST, double dl,
                         double thermalConductivity, double density, double specificHeat);

    // Public member variables (simulation parameters)
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
    double r{};          // diffusion number < 1/4 for 2D stability
    double dt{};         // dt CFL [s]
    double dl{};         // Grid spacing [m]

    // Helper function to calculate derived properties (e.g., thermal diffusivity)
    void calculate_derived_properties();

};

#endif //PROJECT_02_FVM_SIMULATIONPARAMETERS_HPP