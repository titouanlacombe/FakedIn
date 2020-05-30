#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Open the file containing the logs
void log_begin(std::string folder = "");

// Write a string in the log
void log_write(std::string str);

// Close the file containing the logs
void log_end(void);

void load_log();
