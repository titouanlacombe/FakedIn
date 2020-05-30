#pragma once

#include "data_base.h"

//retourne le nombre d'éléments en commun entre deux listes de string
int compatibility(List<std::string>* stra, List<std::string>* strb);

// Recherche d'une companie par son nom
Company* cmp_search_name(List<Company*>* c, std::string name);

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
List<Job*>* job_search_skill(Worker *w, List<Job*> *j, std::string zip_code = "");

// Retourne une liste des jobs proposés par une companie
List<Job*>* job_search_cmp(List<Job*> *j, Company *c);

void load_srch();
