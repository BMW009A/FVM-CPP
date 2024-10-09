//
// Created by QCZ on 9/29/2024.
//

#ifndef PROJECT_02_FVM_OUTPUT_HPP
#define PROJECT_02_FVM_OUTPUT_HPP

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Output {
private:
    ofstream output_file;  // Output file stream

public:
    // Constructor to open the file for writing
    Output(const string& filename);

    // Method to write the header
    void write_header(const vector<string>& column_names);

    // Method to write simulation data (overloaded for vectors or scalars)
    void write_data(const vector<double>& data);
    void write_data(const vector<vector<double>>& data_matrix);

    // Destructor to close the file
    ~Output() = default;

};

#endif //PROJECT_02_FVM_OUTPUT_HPP
