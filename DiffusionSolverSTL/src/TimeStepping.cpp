//
// Created by QCZ on 9/29/2024.
//

#include "TimeStepping.hpp"

void TimeStepping::update(vector<vector<double>> &To, const vector<vector<double>> &T, int N) {
    for (int j = 0; j < N + 2; ++j) {
        for (int i = 0; i < N + 2; ++i) {
            To[j][i] = T[j][i];  // Update To using the new values in T
        }
    }
}

void TimeStepping::update(vector<vector<vector<double>>>& To, const vector<vector<vector<double>>>& T, int N) {
    for (int k = 0; k < N + 2; ++k) {
        for (int j = 0; j < N + 2; ++j) {
            for (int i = 0; i < N + 2; ++i) {
                To[k][j][i] = T[k][j][i];  // Update To using the new values in T
            }
        }
    }
}