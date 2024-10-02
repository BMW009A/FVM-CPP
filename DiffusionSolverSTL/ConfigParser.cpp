//
// Created by QCZ on 9/30/2024.
//

#include "ConfigParser.hpp"

// Function to read the configuration file and store parameters in a map
unordered_map<string, string> ConfigParser::read_config(const string& file_path){

    unordered_map<string, string> config_map;  // Store configuration key-value paris
    ifstream infile(file_path);   // Open the file

    if (!infile.is_open()) {
        cerr << "Error: Could not open configuration file." << endl;
        return config_map;
    }

    string line;
    while (getline(infile, line)) {
        // Ignore comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        istringstream iss(line);
        string value, key;

        // Extract the value (first column) and key (second column)
        iss >> value >> key;

        // Store the value and key in the map
        config_map[key] = value;

    }

    infile.close(); // Close the file
    return config_map;

}

// Function to output the configuration values
void ConfigParser::output_config(const unordered_map<std::string, std::string> &config) {

    cout << "------- Loaded Configuration Parameters --------" << endl;
    for (const auto& pair: config) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "------------------------------------------------" << endl;

}

// Function to validate required keys and values
void ConfigParser::validate_config(const unordered_map<std::string, std::string> &config) {

    // Required parameters (more parameters can be added as the project becomes larger)
    vector<string> required_keys = {"Dimension", "Time_steps", "Output_stride",
                                    "Length_x", "Length_x", "Length_x", "N_x", "N_y", "N_z",
                                    "Thermal_conductivity", "Density", "Specific_heat",
                                    "Temperature_low", "Temperature_high",
                                    "Convergence_criterion", "Solver_type", "Relaxation_factor",
                                    "Linear_solver_type", "Max_iterations", "Solver_tolerance", "Preconditioner_type"
    };

    // Check if all required keys are present
    for (const auto& key : required_keys) {
        if (!key_exists(config, key)) {
            throw runtime_error("Error: Missing required parameter '" + key + "' in the configuration file.");
        }
    }

    //Further validation can be done for specific keys
    int dimension = stoi(config.at("Dimension"));
    if (dimension != 2 && dimension != 3) {
        throw runtime_error("Error: 'Dimension' must be either 2 or 3.");
    }

    int time_steps = stoi(config.at("Time_steps"));
    if (time_steps <= 0) {
        throw runtime_error("Error: 'Time_steps' must be a positive integer.");
    }

    int max_iterations = stoi(config.at("Max_iteration"));
    if (max_iterations <= 0) {
        throw runtime_error("Error: 'Max_iteration' must be greater than 0.");
    }

    double tolerance = stod(config.at("Solver_tolerance"));
    if (tolerance <= 0) {
        throw runtime_error("Error: 'Solver_tolerance' must be greater than 0.");
    }

    // Add more checks as needed.

}

// Helper function to check if a key exists
bool ConfigParser::key_exists(const unordered_map<std::string, std::string> &config, const std::string &key) {

    return config.find(key) != config.end();

}