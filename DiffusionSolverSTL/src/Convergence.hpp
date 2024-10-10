//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_CONVERGENCE_HPP
#define PROJECT_02_FVM_CONVERGENCE_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <variant>
#include "SimulationParameters.hpp"

using namespace std;

class Convergence {
private:
    double tolerance {};
    double residual {};
    int max_iterations {};
    int iteration_count {};
    variant<vector<vector<double>>, vector<vector<vector<double>>>> current_solution;
    variant<vector<vector<double>>, vector<vector<vector<double>>>> prev_solution;
    ofstream log_file;
    SimulationParameters& params;

    // Template function to compute residual for both 2D and 3D
    template<typename T>
    double compute_residual_impl(const T& current_solution, const T& prev_solution);

public:
    // Constructor
    Convergence(double tol, int max_iter, const string& filename, SimulationParameters &params);

    // Method to compute the residual for 2D case (L2 norm by default)
    double compute_residual_2d(const vector<vector<double>>& current_solution);

    // Method to compute the residual for 3D case (L2 norm by default)
    double compute_residual_3d(const vector<vector<vector<double>>>& current_solution);

    // Method to check if convergence criteria are met
    bool check_convergence_2d(const vector<vector<double>>& current_solution);
    bool check_convergence_3d(const vector<vector<vector<double>>>& current_solution);

    // Resets the state of the Convergence class for a new computation
    void reset();

    // Getters for tracking status
    [[nodiscard]] int get_current_iteration() const { return iteration_count; };
    [[nodiscard]] double get_residual() const { return residual; };

    // Print convergence information
    void print_status() const;

    // Output convergence information
    void log_residual();

    // Destructor to close the log file
    ~Convergence() = default;

};

#endif //PROJECT_02_FVM_CONVERGENCE_HPP