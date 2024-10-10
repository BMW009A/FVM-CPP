//
// Created by QCZ on 9/29/2024.
//

#include "Convergence.hpp"
#include <cmath>
#include <variant>

using namespace std;

// Constructor to initialize the tolerance and maximum iterations
Convergence::Convergence(double tol, int max_iter, const string& filename, SimulationParameters &params)
    : params(params),
      tolerance(tol),
      residual(0.0),
      max_iterations(max_iter),
      iteration_count(0) {

    // Initialize current_iteration based on the dimensionality
    if (params.dimension == 2) {
        current_solution = vector<vector<double>>(params.N + 2, vector<double>(params.N + 2, params.TL));
    } else if (params.dimension == 3) {
        current_solution = vector<vector<vector<double>>>(params.N + 2, vector<vector<double>>(params.N + 2, vector<double>(params.N + 2, params.TL)));
    }

    // Open the file for logging residuals
    log_file.open(filename);
    if (!log_file) {
        cerr << "Error: Could not open file " << filename << " for writing residuals.\n";
    } else {
        log_file << "Iteration\tResidual\n";  // Header for the log file
    }
}

// Template function for computing residual
template<typename T>
double Convergence::compute_residual_impl(const T& current_solution, const T& prev_solution) {
    double sum = 0.0;
    for (size_t j = 0; j < current_solution.size(); ++j) {
        for (size_t i = 0; i < current_solution[j].size(); ++i) {
            double diff = current_solution[j][i] - prev_solution[j][i];
            sum += diff * diff;
        }
    }

    // Calculate the L2 norm of the difference between solutions
    return sqrt(sum);
}

// Method to compute the residual for 2D case (L2 norm by default)
// 2D residual calculation
double Convergence::compute_residual_2d(const vector<vector<double>>& current_solution) {
    if (get<vector<vector<double>>>(prev_solution).empty()) {
        prev_solution = current_solution;
        return std::numeric_limits<double>::max();
    }
    residual = compute_residual_impl(get<vector<vector<double>>>(current_solution),
                                     get<vector<vector<double>>>(prev_solution));
    return residual;
}

// Method to compute the residual for 3D case (L2 norm by default)
double Convergence::compute_residual_3d(const vector<vector<vector<double>>> &current_solution) {
    // Ensure we have a previous solution to compare against
    if (get<vector<vector<vector<double>>>>(prev_solution).empty()) {
        prev_solution = current_solution;
        return numeric_limits<double>::max(); // Return a large initial residual
    }
    residual = compute_residual_impl(get<vector<vector<vector<double>>>>(current_solution),
                                     get<vector<vector<vector<double>>>>(prev_solution));

    // Calculate the L2 norm of the difference between solutions
    return residual;
}

// Method to check if convergence criteria are met for 2D case
bool Convergence::check_convergence_2d(const vector<vector<double>> &current_solution) {
    iteration_count++;
    // Compute the current residual
    compute_residual_2d(current_solution);

    // Print current iteration and residual status
    print_status();

    // Update the previous solution
    prev_solution = current_solution;

    // Check if the residual is smaller than the tolerance or max iterations exceeded
    return (residual < tolerance || iteration_count >= max_iterations);
}

// Method to check if convergence criteria are met for 3D case
bool Convergence::check_convergence_3d(const vector<vector<vector<double>>> &current_solution) {
    iteration_count++;
    // Compute the current residual
    compute_residual_3d(current_solution);

    // Print current iteration and residual status
    print_status();

    // Update the previous solution
    prev_solution = current_solution;

    // Check if the residual is smaller than the tolerance or max iterations exceeded
    return (residual < tolerance || iteration_count >= max_iterations);
}


// Resets the state of the Convergence class for a new computation
void Convergence::reset() {
    residual = 0.0;
    iteration_count = 0;
    prev_solution = {};
}

// Print convergence information
void Convergence::print_status() const {
    cout << "Iteration: " << iteration_count << " | Residual: " << residual << endl;
}

// Output convergence information
void Convergence::log_residual() {
    if (log_file) {
        log_file << iteration_count << "\t" << residual << "\n";
    }
}