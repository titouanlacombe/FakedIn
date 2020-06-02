#pragma once

#include "data_base.h"

// Rechercher parmi les chercheurs d'emploi pour des profils qui 
// correspondent à un poste à pourvoir (recherche par zip_code ou pas)
List<Worker>* srch_wrk_profile_job(List<Worker*> *workers, Job* j, bool zip_code);

// Rechercher parmi les jobs ceux qui correspondent
// au profil de w (recherche par zip_code ou pas)
List<Job>* srch_job_profile_wrk(List<Job*> *jobs, Worker* w, bool zip_code);

// Retourne colleagues employés par company
List<Worker>* srch_coll_from_cmp(Worker *w, Company *c);

// retourne les anciens collègues employés aux entreprises 
// qui recherchent les compétences de w
List<Worker>* srch_coll_skills(List<Job*> *jobs, Worker *w);

void load_srch();
