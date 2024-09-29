//
// Created by QCZ on 9/29/2024.
//

#include "TimeStepping.hpp"

void TimeStepping::update(vector<vector<double>>& To, const vector<vector<double>>& T, int N) {
    for (int j = 0; j < N + 1; ++j) {
        for (int i = 0; i < N + 1; ++i) {
            To[j][i] = T[j][i];
        }
    }
}