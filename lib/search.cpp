#include "search.h"

List<Worker*>* cmp_search_wrk(Company *c, Job *j, bool zip_code)
{

	return NULL;
}

List<Worker*>* wrk_search_wrk_by_cmp(Worker *w, Company *c)
{
	List<Worker*>* res = new List<Worker*>;
	Node<Worker*>* temp = w->colleagues->first;

	while(temp){
		if(temp->data->company == c){
			res->addlast(temp->data);
		}
		temp = temp->next;
	}

	return res;
}

List<Worker*>* wrk_search_wrk_by_skill(Worker *w)
{
	return NULL;
}

List<Worker*>* wrk_search_job(Worker *w, bool zip_code)
{
	return NULL;
}