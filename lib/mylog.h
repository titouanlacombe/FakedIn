#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Open the log file
void log_begin(std::string folder = "");

// Write str in the log file
void log_write(std::string str);

// Close the log file
void log_end(void);

void load_log();
