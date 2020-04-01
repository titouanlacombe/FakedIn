#pragma once

// Open the file containing the logs
void log_begin(void);

// Write a string in the log
void log_write(char *);

// Close the file containing the logs
void log_end(void);