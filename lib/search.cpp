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
	Node<Worker*>* temp = w->first;

	while(temp){
		if((zip_code == "") || (zip_code == temp->data->zip_code)){
			if(compatibility(j->skills, temp->data->skills) > 0){
				res->addlast(temp->data);
			}
		}
		temp = temp->next;
	}

	return res;
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