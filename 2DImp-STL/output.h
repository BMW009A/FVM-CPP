//
// Created by QCZ on 9/24/2024.
//

#ifndef PROJECT_02_FVM_OUTPUT_H
#define PROJECT_02_FVM_OUTPUT_H

#include <vector>   // Include vector header
#include <string>   // Include string header (for filename)

using namespace std;

// Declare the function to output 3D vector to a file
void outputResultsToFile(const vector<vector<vector<double>>>& Ts, const string& filename);

#endif //PROJECT_02_FVM_OUTPUT_H
