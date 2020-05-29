#include "search.h"

int compatibility(List<std::string>* str_a, List<std::string>* str_b){
	int res = 0;
	Node<std::string>* cur_a = str_a->first;
	Node<std::string>* cur_b;

	while(cur_a){
		cur_b = str_b->first;
		while(cur_b){
			if(cur_a->data == cur_b->data){
				res++;
			}
			cur_b = cur_b->next;
		}
		cur_a = cur_a->next;
	}

	return res;
}

List<Worker*>* cmp_search_wrk(List<Worker*> *w, Company *c, Job *j, std::string zip_code)
{
	List<Worker*>* res = new List<Worker*>;
	Node<Worker*>* cur = w->first;

	while(cur){
		if((zip_code == "") || (zip_code == cur->data->zip_code)){
			if(compatibility(j->skills, cur->data->skills) > 0){
				res->addlast(cur->data);
			}
		}
		cur = cur->next;
	}

	return res;
}

List<Worker*>* wrk_search_wrk_by_cmp(Worker *w, Company *c)
{
	List<Worker*>* res = new List<Worker*>;
	Node<Worker*>* cur = w->colleagues->first;

	while(cur){
		if(cur->data->company == c){
			res->addlast(cur->data);
		}
		cur = cur->next;
	}

	return res;
}

List<Worker*>* wrk_search_wrk_by_skill(Worker *w, List<Job*> *j)
{
	// List<Worker*>* res = new List<Worker*>;
	// Node<Worker*>* cur = w->colleagues->first;


	return NULL;
}

List<Job*>* wrk_search_job(Worker *w, List<Job*> *j, std::string zip_code)
{
	List<Job*>* res = new List<Job*>;
	Node<Job*>* cur = j->first;

	while(cur){
		if((zip_code == "") || (zip_code == cur->data->company->zip_code)){
			if(compatibility(cur->data->skills, w->skills)){
				res->addlast(cur->data);
			}
		}	
		cur = cur->next;
	}

	return res;
}