#pragma once

#include "list.h"
#include "company.h"
#include "job.h"
#include "worker.h"

// Reads the data base and creates the 3 lists of objects
void load(List<Job*>& jobs, List<Worker*>& workers, std::string folder = "data_base");

// Stores the 3 lists of objects in the data base
void save(List<Job*>& jobs, List<Worker*>& workers, std::string folder = "data_base");
