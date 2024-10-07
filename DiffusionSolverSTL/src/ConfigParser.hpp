//
// Created by QCZ on 9/30/2024.
//

#ifndef PROJECT_02_FVM_CONFIGPARSER_HPP
#define PROJECT_02_FVM_CONFIGPARSER_HPP

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class ConfigParser {
public:
    // Function to read the configuration file and store parameters in a map
    unordered_map<string, string> read_config(const string& file_path);

    // Function to validate the config values
    void validate_config(const unordered_map<string, string>& config);

    // Function to output the config values
    void output_config(const unordered_map<string, string>& config);

private:
    // Helper function for checking if a key exists
    bool key_exists(const unordered_map<string, string>& config, const string& key);
};

#endif //PROJECT_02_FVM_CONFIGPARSER_HPP