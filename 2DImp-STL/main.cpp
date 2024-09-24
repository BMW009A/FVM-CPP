//
// Created by QCZ on 2024/09/14.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "output.h"

using namespace std;

int main(){

// Definition
    double L = 1.0;         // cavity length [m]
    int N = 20;             // number of girds [-]
    double dl = L / N;      // grid spacing [m]
    double TL = 300.0;      // low temperature  [K]
    double TH = 500.0;      // high temperature [K]
    double crit = 0.01;     // criteria for convergence [K]
    double a = 1.0;         // heat diffusivity [m2/s]
    double r = 0.1;         // diffusion number < 1/4for 2D
    double dt = r / a * dl * dl; // dt CFL  0.01

//  NO   = 5000   #time step
    int NO = 2000;     // time step
    int ST = 100;       // output stride

    // Natural property
    // Values for water
    double lm = 0.6;
    double rhoCp = 4.182 * 1.25;  // volumetric specific heat [J/m3s]
    double alpha = lm / rhoCp;  // thermal diffusivity [m2/s]

    // Grid
    vector<double> x(N + 2, 0.0);
    vector<double> dx(N + 2, 0.0);

    x[0] = 0.0;
    dx[0] = 0.0;
    dx[N + 1] = 0.0;

    for (int i = 1; i < N + 1; ++i) {
        dx[i] = dl;
    }

    for (int i = 1; i < N + 2; ++i) {
        x[i] = x[i - 1] + 0.5 * (dx[i] + dx[i - 1]);
    }

    std::vector<double> dy(dx);  // Copy dx to dy and x to y
    std::vector<double> y(x);

//    for (int i = 0; i < N + 2; ++i) {
//        cout << "coordination of each grid point on x-axis: " << x[i] << endl;
//        cout << "coordination of each grid point on y-axis: " << y[i] << endl;
//    }

    // Coefficient
    vector<double> ce(N + 1, 0.0);
    vector<double> cw(N + 1, 0.0);
    vector<double> cn(N + 1, 0.0);
    vector<double> cs(N + 1, 0.0);

    vector<vector<double>> co(N + 1, vector<double>(N + 1));
    vector<vector<double>> cd(N + 1, vector<double>(N + 1));

    for (int i = 1; i < N + 1; ++i) {

        ce[i] = lm * dl / (0.5 * (dx[i] + dx[i + 1]));
        cw[i] = lm * dl / (0.5 * (dx[i] + dx[i - 1]));
        cn[i] = lm * dl / (0.5 * (dy[i] + dy[i + 1]));
        cs[i] = lm * dl / (0.5 * (dy[i] + dy[i - 1]));

    }

    for (int j = 1; j < N + 1; ++j) {
        for (int i = 1; i < N + 1; ++i) {

            co[j][i] = rhoCp * dx[i] * dy[j] / dt;
            cd[j][i] = (co[j][i] + ce[i] + cw[i] + cn[j] + cs[j]);
//            cout << "coefficients of co on the grid points: " << co[j][i] << endl;

        }
    }

    // T(y, x) is temperature, Tp(y, x) is predicted temperature
    vector<std::vector<double>> T(N + 2, vector<double>(N + 2));
    vector<std::vector<double>> Tp(N + 2, vector<double>(N + 2));
    vector<std::vector<double>> To(N + 2, vector<double>(N + 2));

    for (int j = 0; j < N + 2; ++j) {
        for (int i = 0; i < N + 2; ++i) {
            T[j][i] = TL;
        }
    }

    // Boundary condition
    for (int i = 0; i < N + 2; ++i) {
        T[N + 1][i] = TH;
    }

    cout << "Temperature distribution on the grid: " << endl;

    for (int j = 0; j < N + 2; ++j) {
        for (int i = 0; i < N + 2; ++i) {

            cout << T[j][i] <<  " ";

        }

        cout << endl;

    }

    // Initial & prediction values
    for (int j = 1; j < N + 2; ++j) {
        for (int i = 1; i < N + 2; ++i) {
            Tp[j][i] = T[j][i];
            To[j][i] = T[j][i];
        }
    }

    int flg = 0;
    int l = 0;

    // Ts (to store the output data)
    vector<vector<vector<double>>> Ts;

    // Loop forward in time
    for (size_t n = 0; n < NO; ++n) {

        // Iteration loop
        flg = 1;
        l = 0;

        while (flg == 1){

            flg = 0;
            l += 1;

            // Data store
            if (n % ST == 0) {

                cout << "time= " << n << endl;
                Ts.push_back(T);

            }

            for (size_t j = 1; j < N + 1; ++j) {
                for (size_t i = 1; i < N + 1; ++i) {
                    // Calculation
                    T[j][i] = (ce[i] * To[j][i + 1] +
                               cw[i] * To[j][i - 1] +
                               cn[j] * To[j + 1][i] +
                               cs[j] * To[j - 1][i] +
                               (co[j][i] - ce[i] - cw[i] - cn[j] - cs[j])
                               * To[j][i]) / co[j][i];
                }
            }

            // Convergence check
            for (size_t j = 1; j < N + 1; ++j) {
                for (size_t i = 1; i < N + 1; ++i) {

                    if (abs(T[j][i] - Tp[j][i]) > crit){
                        flg = 1;
                    }
                }
            }

            // Update date for next iteration
            for (size_t j = 1; j < N + 1; ++j) {
                for (size_t i = 1; i < N + 1; ++i) {

                    Tp[j][i] = T[j][i];

                }
            }

            if (l % 10 == 0) {
                cout << "Itr= " << l << endl;
            }

        }

        // Update the prediction value of grid for next time step
        for (size_t j = 1; j < N + 1; ++j) {
            for (size_t i = 1; i < N + 1; ++i) {

                To[j][i] = T[j][i];

            }
        }


    }

    // Call the function to write the results to a file
    outputResultsToFile(Ts, R"(C:\Users\QCZ\CLionProjects\Project-02-FVM\2DImp-STL\computation_results.txt)");

    return 0;

}