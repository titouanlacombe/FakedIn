#pragma once

#include "data_base.h"

class Network
{
public:
	List<Worker*>* workers;

	Network();
	~Network();

	//retourne la taille du Network
	int size();
	void addWorker(Worker* w);
};

//determine s'il existe une chaine de collegues entre deux travailleurs
bool linked(Worker *a, Worker *b);

// Recherche des seekers par skill et zip code (optionel) correspondant à un job
List<Worker*>* cmp_search_wrk(Company *c, Job *j, bool zip_code = false);

// Recherche des colleagues par company (retourne colleagues employer par company)
List<Worker*>* wrk_search_wrk_by_cmp(Worker *w, Company *c);
// Recherche des colleagues par skill (retourne colleagues 
// employer aux companies dont job require les skill du seeker)
List<Worker*>* wrk_search_wrk_by_skill(Worker *w);

// Recherche des jobs par skills et zip code (optionel)
List<Worker*>* wrk_search_job(Worker *w, bool zip_code = false);
