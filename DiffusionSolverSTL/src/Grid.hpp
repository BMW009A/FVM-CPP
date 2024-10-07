//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_GRID_HPP
#define PROJECT_02_FVM_GRID_HPP

#include <vector>

using namespace std;

class Grid {
public:
    // Constructor to initialize the grid with given parameters
    Grid(int N, double L, double lm, double rhoCp, double dt);

    // Function to initialize the coefficients
    void initialize_coefficients();


    // Grid variables
    int N;
    double L;
    double dl;

    // Heat conduction properties
    double lm;
    double rhoCp;
    double dt;

    // Grid coordinates and spacing
    vector<double> x;              // x-coordinates
    vector<double> y;              // x-coordinates
    vector<double> dx;             // Grid spacing in x-direction
    vector<double> dy;             // Grid spacing in y-direction

    // Conduction coefficients
    vector<double> ce, cw, cn, cs;      // East, West, North, South conduction coefficients
    vector<vector<double>> co, cd;              // coefficients for the finite volume equation

private:
    // Internal function to initialize grid points and spacing
    void initialize_grid();
};

#endif //PROJECT_02_FVM_GRID_HPP