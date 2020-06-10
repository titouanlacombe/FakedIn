#pragma once

#include <string>

// Open the log file
void log_begin(std::string folder = "", bool automated_file_name = true);

// Write str in the log file
void log_write(std::string str, bool automated_line_prefix = true);

// Close the log file
void log_end(void);

//-----------------Usefull functions-----------------
// Return the time as an string
std::string get_time_str(bool longstr = true, time_t *elapsed = NULL);

// Dump s in the console (usefull for debug)
void dump_str(std::string s);

// Imits getline behavior but with a string and not a stream
int mygetline(std::string& s, std::string& dest, char limit = '\n');

// Return true if path exists
inline bool path_exist(const std::string& path);

// Create a folder if 'folder' does not exist
void check_folder(std::string folder);
