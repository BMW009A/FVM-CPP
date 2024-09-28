//
// Created by QCZ on 9/27/2024.
//

#ifndef PROJECT_02_FVM_OUTPUT_HPP
#define PROJECT_02_FVM_OUTPUT_HPP

#include <vector>   // Include vector header
#include <string>   // Include string header (for filename)

using namespace std;

// Declare the function to output 3D vector to a file
void outputResultsToFile(const vector<vector<vector<double>>>& Ts, const string& filename);

#endif //PROJECT_02_FVM_OUTPUT_HPP
