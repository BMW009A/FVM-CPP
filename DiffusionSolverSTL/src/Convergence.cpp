//
// Created by QCZ on 9/29/2024.
//

#include "Convergence.hpp"
#include <cmath>

using namespace std;

// Constructor to initialize the tolerance and maximum iterations
Convergence::Convergence(double tol, int max_iter, const string& filename)
    : tolerance(tol), residual(0.0), max_iterations(max_iter), current_iteration(0) {
    // Open the file for logging residuals
    log_file.open(filename);
    if (!log_file) {
        cerr << "Error: Could not open file " << filename << " for writing residuals.\n";
    } else {
        log_file << "Iteration\tResidual\n";  // Header for the log file
    }
}

// Method to compute the residual (L2 norm by default)
double Convergence::compute_residual(const vector<double>& current_solution) {

    // Ensure we have a previous solution to compare against
    if (prev_solution.empty()) {
        prev_solution = current_solution;
        return numeric_limits<double>::max(); // Return a large initial residual
    }

    double sum = 0.0;
    for (size_t i = 0; i < current_solution.size(); ++i) {
        double diff = current_solution[i] - prev_solution[i];
        sum += diff * diff;
    }

    // Calculate the L2 norm of the difference between solutions
    residual = sqrt(sum);
    return residual;
}

// Method to check if convergence criteria are met
bool Convergence::check_convergence(const vector<double>& current_solution) {
    current_iteration++;

    // Compute the current residual
    compute_residual(current_solution);

    // Print current iteration and residual status
    print_status();

    // Update the previous solution
    prev_solution = current_solution;

    // Check if the residual is smaller than the tolerance or max iterations exceeded
    return (residual < tolerance || current_iteration >= max_iterations);
}

// Resets the state of the Convergence class for a new computation
void Convergence::reset() {
    residual = 0.0;
    current_iteration = 0;
    prev_solution.clear();
}

// Getters for tracking status
int Convergence::get_current_iteration() const {
    return current_iteration;
}

double Convergence::get_residual() const {
    return residual;
}

// Print convergence information
void Convergence::print_status() const {
    cout << "Iteration: " << current_iteration << " | Residual: " << residual << endl;
}

// Output convergence information
void Convergence::log_residual() {
    if (log_file) {
        log_file << current_iteration << "\t" << residual << "\n";
    }
}