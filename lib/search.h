#pragma once

#include "data_base.h"

//retourne le nombre d'éléments en commun entre deux listes de string
int compatibility(List<std::string>* stra, List<std::string>* strb);

// Recherche d'une companie par son nom
Company* cmp_search_name(List<Company*>* c, std::string name);

// Recherche d'un worker par son nom et prénom
Worker* wrk_search_name(List<Worker*>* w, std::string name, std::string surname);

// Rechercher un job à partir d'un titre et d'une companie
Job* job_search_name_cmp(List<Job*>* j, Company* c,std::string name);

// Recherche des seekers par skill et zip code (optionel) correspondant à un job
List<Worker*>* seek_search_skill(List<Worker*> *w, Company *c, Job *j, std::string zip_code = "");

// Recherche des colleagues par company (retourne colleagues employés par company)
List<Worker*>* coll_search_cmp(Worker *w, Company *c);

// Recherche des colleagues par skill (retourne les anciencs collègues 
// employés aux companies qui recherchent les skill du worker)
List<Worker*>* emp_search_job(Worker *w, List<Job*> *j);

// Recherche des jobs par skills et zip code (optionel)
List<Job*>* job_search_skill(Worker *w, List<Job*> *j, std::string zip_code = "");

// Retourne une liste des jobs proposés par une companie
List<Job*>* job_search_cmp(List<Job*> *j, Company *c);