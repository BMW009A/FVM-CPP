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

    // Virtual function that each derived class must implement (function overloaded for 2D and 3D cases)
    virtual void step(vector<vector<double>>& T, vector<vector<double>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<double>>>& Ts) = 0;

    virtual void step(vector<vector<vector<double>>>& T, vector<vector<vector<double>>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<vector<double>>>>& Ts) = 0;

    // Function to update temperature field (same for all schemes(derived classes))
    // Function overloaded for 2D and 3D cases
    static void update(vector<vector<double>>& To, const vector<vector<double>>& T, int N);

    static void update(vector<vector<vector<double>>>& To, const vector<vector<vector<double>>>& T, int N);

};

#endif //PROJECT_02_FVM_TIMESTEPPING_HPP