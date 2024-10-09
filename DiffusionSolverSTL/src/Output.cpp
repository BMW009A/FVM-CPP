//
// Created by QCZ on 9/29/2024.
//

#include "Output.hpp"
#include <iostream>
#include <iomanip>  //For controlling output precision

using namespace std;

// Constructor: Opens the file for writing
Output::Output(const std::string &filename) {
    output_file.open(filename);
    if (!output_file) {
        cerr << "Error: Could not open file " << filename << " for writing simulation results.\n";
    }
}

// Write the header (column names) for the output file
void Output::write_header(const vector<std::string> &column_names) {
    if (output_file) {
        for (const auto& col : column_names) {
            output_file << col << "\t";  // Tab-separated
        }
        output_file << "\n";  // Newline at the end of the header
    }
}

// Write a single row of data (for vector output, 1D data like temperature)
void Output::write_data(const vector<double> &data) {
    if (output_file) {
        for (const auto& val : data) {
            output_file << fixed << setprecision(6) << val << "\t";  // Write each value with 6 decimal precision
        }
        output_file << "\n";  // Newline at the end of the header
    }
}

// Write a matrix of data (for 2D output, e.g., temperature field)
void Output::write_data(const vector<vector<double>> &data_matrix) {
    if (output_file) {
        for (const auto& row : data_matrix) {
            write_data(row);
        }
    }
}