//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_CONVERGENCE_HPP
#define PROJECT_02_FVM_CONVERGENCE_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class Convergence {
private:
    double tolerance;
    double residual;
    int max_iterations;
    int current_iteration;
    vector<double> prev_solution;
    ofstream log_file;

public:
    // Constructor
    Convergence(double tol, int max_iter, const string& filename);

    // Method to compute the residual (L2 norm by default)
    double compute_residual(const vector<double>& current_solution);

    // Method to check if convergence criteria are met
    bool check_convergence(const vector<double>& current_solution);

    // Resets the state of the Convergence class for a new computation
    void reset();

    // Getters for tracking status
    [[nodiscard]] int get_current_iteration() const;
    [[nodiscard]] double get_residual() const;

    // Print convergence information
    void print_status() const;

    // Output convergence information
    void log_residual();

    // Destructor to close the log file
    ~Convergence() = default;

};

#endif //PROJECT_02_FVM_CONVERGENCE_HPP