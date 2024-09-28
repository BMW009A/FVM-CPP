//
// Created by QCZ on 9/24/2024.
//

#include "output.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void outputResultsToFile(const std::vector<std::vector<std::vector<double>>>& Ts, const std::string& filename) {
    std::ofstream outFile(filename);

    // Check if the file is successfully opened
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Iterate through the 3D vector and write data to the file
    for (size_t timeStep = 0; timeStep < Ts.size(); ++timeStep) {
        outFile << "Time Step: " << timeStep << "\n";
        for (size_t j = 0; j < Ts[timeStep].size(); ++j) {
            for (size_t i = 0; i < Ts[timeStep][j].size(); ++i) {
                outFile << Ts[timeStep][j][i] << " ";  // Write each value
            }
            outFile << "\n";  // Newline after each row
        }
        outFile << "----------\n";  // Separator between time steps
    }

    outFile.close();
    std::cout << "Computation results written to '" << filename << "'\n";
}