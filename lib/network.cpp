#include "network.h"

Network::Network()
{
  
}

Network::~Network()
{
  delete(workers);
}

int Network::size()
{
	return (workers->length);
}

void Network::addWorker(Worker* w)
{
	workers->addlast(w);
}

bool linked(Worker *a, Worker *b)
{
	
	return false;
}

List<Worker*>* cmp_search_wrk(Company *c, Job *j, bool zip_code)
{
	return NULL;
}

List<Worker*>* wrk_search_wrk_by_cmp(Worker *w, Company *c)
{
	
	return NULL;
}

List<Worker*>* wrk_search_wrk_by_skill(Worker *w)
{
	return NULL;
}

List<Worker*>* wrk_search_job(Worker *w, bool zip_code)
{
	return NULL;
}
