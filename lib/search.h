#pragma once

#include "data_base.h"

// Recherche d'une companie par son nom
Company* cmp_login(List<Company*>* companies, std::string name);

// Recherche d'un worker par son nom et prénom
Worker* wrk_login(List<Worker*>* workers, std::string first_name, std::string last_name);

// Rechercher un job à partir d'un titre et d'une companie
Job* job_login(List<Job*>* jobs, Company* c, std::string title);

// Rechercher parmi les chercheurs d'emploi pour des profils qui 
// correspondent à un poste à pourvoir (recherche par zip_code ou pas)
List<Worker*>* srch_wrk_profile_job(List<Worker*> *workers, Job* j, bool zip_code);

// Rechercher parmi les jobs ceux qui correspondent
// au profil de w (recherche par zip_code ou pas)
List<Job*>* srch_job_profile_wrk(List<Job*> *jobs, Worker* w, bool zip_code);

// Retourne colleagues employés par company
List<Worker*>* srch_coll_from_cmp(Worker *w, Company *c);

// retourne les anciens collègues employés aux entreprises 
// qui recherchent les compétences de w
List<Worker*>* srch_coll_skills(Worker *w, List<Job*> *jobs);

void load_srch();
