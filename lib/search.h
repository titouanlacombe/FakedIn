#pragma once

#include "data_base.h"

//determine s'il existe une chaine de collegues entre deux travailleurs
bool linked(Worker *a, Worker *b);

// Recherche des seekers par skill et zip code (optionel) correspondant à un job
List<Worker*>* cmp_search_wrk(Company *c, Job *j, bool zip_code = false);

// Recherche d'un worker par son nom et prénom
Worker* wrk_search_name(List<Worker*>* w, std::string name, std::string surname);

// Rechercher un job à partir d'un titre et d'une companie
Job* job_search_name(List<Job*>* j, Company* c,std::string name);

// Recherche des seekers ayant au moins un skill d'une liste de skills (+ zip code optionel)
List<Worker*>* seek_search_skill(List<Worker*> *w, List<std::string>* skills, std::string zip_code = "");

// Recherche des colleagues par company (retourne colleagues employés par company)
List<Worker*>* coll_search_cmp(Worker *w, Company *c);

// Recherche des colleagues par skill (retourne les anciencs collègues 
// employés aux companies qui recherchent les skill du worker)
List<Worker*>* coll_search_skill(Worker *w, List<Job*> *j);

// Recherche des jobs par skills et zip code (optionel)
List<Worker*>* wrk_search_job(Worker *w, bool zip_code = false);
