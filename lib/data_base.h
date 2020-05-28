#pragma once

#include "worker.h"
#include "job.h"

//lis les 4 bases de données et construit les listes correspondantes
void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers);

//utilise les listes données en paramètre pour écrire les 4 bases de données
void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers);
