//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_IMPLICITSCHEME_HPP
#define PROJECT_02_FVM_IMPLICITSCHEME_HPP

#include "TimeStepping.hpp"
#include "Grid.hpp"

class ImplicitScheme : public TimeStepping {
public:
    // Override the step function for the explicit scheme
    void step(vector<vector<double>>& T, vector<vector<double>>& To,
                      Grid& grid, int time_step_num, int output_stride,
                      vector<vector<vector<double>>>& Ts) override;

    void step(vector<vector<vector<double>>>& T, vector<vector<vector<double>>>& To,
              Grid& grid, int time_step_num, int output_stride,
              vector<vector<vector<vector<double>>>>& Ts) override;
};

#endif //PROJECT_02_FVM_IMPLICITSCHEME_HPP
