#pragma once

#include "data_base.h"

//retourne le nombre d'éléments en commun entre deux listes de string
int compatibility(List<std::string>* stra, List<std::string>* strb);

// Recherche des seekers par skill et zip code (optionel) correspondant à un job
List<Worker*>* cmp_search_wrk(List<Worker*> *w, Company *c, Job *j, std::string zip_code = "");

// Recherche des colleagues par company (retourne colleagues employer par company)
List<Worker*>* wrk_search_wrk_by_cmp(Worker *w, Company *c);

// Recherche des colleagues par skill (retourne colleagues 
// employés aux companies qui propose un job qui nécessite les skill du seeker)
List<Worker*>* wrk_search_wrk_by_skill(Worker *w, List<Job*> *j);

// Recherche des jobs par skills et zip code (optionel)
List<Job*>* wrk_search_job(Worker *w, List<Job*> *j, std::string zip_code = "");
