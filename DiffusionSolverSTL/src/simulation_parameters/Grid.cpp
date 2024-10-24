//
// Created by QCZ on 9/29/2024.
//

#include "Grid.hpp"
#include <vector>

// Constructor: Initializes grid variables and allocates memory for coefficients
Grid::Grid(int N, double L, double lm, double rhoCp, double dt)
    : N(N), L(L), lm(lm), rhoCp(rhoCp), dt(dt),
    dl(L / N),  // Calculate grid spacing based on N and L
    x(N + 2, 0.0), y(N + 2, 0.0), z(N + 2, 0.0), // Initialize grid coordinates
    dx(N + 2, 0.0), dy(N + 2, 0.0), dz(N + 2, 0.0), // Initialize grid spacing vectors
    ce(vector<double>(N + 1, 0.0)),
    cw(vector<double>(N + 1, 0.0)),
    cn(vector<double>(N + 1, 0.0)),
    cs(vector<double>(N + 1, 0.0)),
    cf(vector<double>(N + 1, 0.0)),
    cb(vector<double>(N + 1, 0.0)),
    co2D(N + 1, vector<double>(N + 1, 0.0)),
    cd2D(N + 1, vector<double>(N + 1, 0.0)),
    co3D(N + 1, vector<vector<double>>(N + 1, vector<double>(N + 1, 0.0))),
    cd3D(N + 1, vector<vector<double>>(N + 1, vector<double>(N + 1, 0.0)))
{

    // Initialize grid points and spacing
    initialize_grid();

}

// Initialize grid points (x, y coordinates) and spacing (dx, dy)
void Grid::initialize_grid() {
    // Initialize dx and dy (grid spacing) and x and y (grid coordinates)
    dx[0] = 0.0;
    dy[0] = 0.0;
    dz[0] = 0.0;
    dx[N + 1] = 0.0;
    dy[N + 1] = 0.0;
    dz[N + 1] = 0.0;

    // Assign default grid spacing to the interior points
    for (int i = 0; i < N + 1; ++i) {
        dx[i] = dl;  // Constant grid spacing in x-direction
        dy[i] = dl;  // Constant grid spacing in y-direction
        dz[i] = dl;  // Constant grid spacing in z-direction
    }

    // Initialize the grid coordinates using dx and dy
    for (int i = 1; i < N + 2; ++i) {
        x[i] = x[i - 1] + 0.5 * (dx[i] + dx[i - 1]);
        y[i] = y[i - 1] + 0.5 * (dy[i] + dy[i - 1]);
        z[i] = z[i - 1] + 0.5 * (dz[i] + dz[i - 1]);
    }

}

// Initialize coefficients (ce, cw, cn, cs, co, cd)
void Grid::initialize_coefficients() {
    // Loop over all grid points and calculate coefficients
    for (int i = 0; i < N + 1; ++i) {
        ce[i] = lm * dl / (0.5 * (dx[i] + dx[i + 1]));  // East coefficient
        cw[i] = lm * dl / (0.5 * (dx[i] + dx[i - 1]));  // West coefficient
        cn[i] = lm * dl / (0.5 * (dy[i] + dy[i + 1]));  // North coefficient
        cs[i] = lm * dl / (0.5 * (dy[i] + dy[i - 1]));  // South coefficient
        cf[i] = lm * dl / (0.5 * (dz[i] + dz[i + 1]));  // Front coefficient
        cb[i] = lm * dl / (0.5 * (dz[i] + dz[i - 1]));  // Back coefficient
    }

    // Loop through the grid to calculate co and cd for 2D cases
    for (int j = 0; j < N + 1; ++j) {
        for (int i = 0; i < N + 1; ++i) {
            co2D[j][i] = rhoCp * dx[i] * dy[j] / dt;
            cd2D[j][i] = co2D[j][i] + ce[i] + cw[i] + cn[j] + cs[j];
        }
    }

    // Loop through the grid to calculate co and cd for 3D cases
    for (int k = 0; k < N + 1; ++k) {
        for (int j = 0; j < N + 1; ++j) {
            for (int i = 0; i < N + 1; ++i) {
                co3D[k][j][i] = rhoCp * dx[i] * dy[j] / dt;
                cd3D[k][j][i] = co3D[k][j][i] + ce[i] + cw[i] + cn[j] + cs[j];    // TODO: This is not correct for now, need derivation
            }
        }
    }
}