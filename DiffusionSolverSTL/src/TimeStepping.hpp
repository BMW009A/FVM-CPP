//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_TIMESTEPPING_HPP
#define PROJECT_02_FVM_TIMESTEPPING_HPP

#include <vector>
#include "Grid.hpp"

using namespace std;

class TimeStepping {
public:
    virtual ~TimeStepping() = default;

    // Virtual function that each derived class must implement
    virtual void step(vector<vector<double>>& T, vector<vector<double>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<double>>>& Ts) = 0;

    // Function to update temperature field (same for all schemes(derived classes))
    static void update(vector<vector<double>>& To, const vector<vector<double>>& T, int N) {
        for (int j = 0; j < N + 1; ++j) {
            for (int i = 0; i < N + 1; ++i) {
                To[j][i] = T[j][i];
            }
        }
    }
};

#endif //PROJECT_02_FVM_TIMESTEPPING_HPP