#pragma once

#include "worker.h"
#include "job.h"

void dump_str(std::string s);

int mygetline(std::string& s, std::string& dest, char limit = '\n');

//lis les 4 bases de données et construit les listes correspondantes
void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder = "data_base");

//utilise les listes données en paramètre pour écrire les 4 bases de données
void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder = "data_base");

void load_db();
