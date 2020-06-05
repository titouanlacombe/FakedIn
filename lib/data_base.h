#pragma once

#include "worker.h"
#include "job.h"

// Dump s in the console (usefull for debug)
void dump_str(std::string s);

// Imits getline behavior but with a string and not a stream
int mygetline(std::string& s, std::string& dest, char limit = '\n');

// Reads the data base and creates the 3 lists of objects
void load(List<Company*>& companies, List<Job*>& jobs, List<Worker*>& workers, std::string folder = "data_base");

// Stores the 3 lists of objects in the data base
void save(List<Company*>& companies, List<Job*>& jobs, List<Worker*>& workers, std::string folder = "data_base");

void load_db();
