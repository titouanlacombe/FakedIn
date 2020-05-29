#include "search.h"

int compatibility(List<std::string>* str_a, List<std::string>* str_b)
{
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

Company* cmp_search_name(List<Company*>* c, std::string name)
{
	Company* res = new Company;
	Node<Company*>* cur = c->first;

	while(cur){
		if(cur->data->name == name){
			res = cur->data;
		}
		cur = cur->next;
	}

	if(res->name == ""){
		res = NULL;
	}
	return res;
}

Worker* wrk_search_name(List<Worker*>* w, std::string name, std::string surname)
{
	Worker* res = new Worker;
	Node<Worker*>* cur = w->first;

	while(cur){
		if(cur->data->first_name == name && cur->data->last_name == surname){
			res = cur->data;
		}
		cur = cur->next;
	}

	if(res->first_name == ""){
		res = NULL;
	}
	return res;
}

Job* job_search_name_cmp(List<Job*>* j, Company* c, std::string name)
{
	Job* res = new Job;
	Node<Job*>* cur = j->first;

	while(cur){
		if(cur->data->title == name && cur->data->company == c){
			res = cur->data;
		}
		cur = cur->next;
	}

	if(res->title == ""){
		res = NULL;
	}
	return res;
}

List<Worker*>* seek_search_skill(List<Worker*> *w, Company *c, Job *j, std::string zip_code)
{
	List<Worker*>* res = new List<Worker*>;
	Node<Worker*>* cur = w->first;

	while(cur){
		if(!cur->data->employed()){
			if((zip_code == "") || (zip_code == cur->data->zip_code)){
				if(compatibility(j->skills, cur->data->skills) > 0){
					res->addlast(cur->data);
				}
			}
			cur = cur->next;
		}
	}

	return res;
}

List<Worker*>* coll_search_cmp(Worker *w, Company *c)
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

List<Worker*>* emp_search_job(Worker *w, List<Job*> *j)
{
	List<Worker*>* res = new List<Worker*>;
	Node<Worker*>* cur_w = w->colleagues->first;
	Node<Job*>* cur_j = j->first;

	while(cur_w){
		while(cur_j){
			if(cur_j->data->company == cur_w->data->company){
				if(compatibility(cur_j->data->skills, w->skills) > 0){
					res->addlast(cur_w->data);
				}
			}
			cur_j = cur_j->next;
		}
		cur_w = cur_w->next;
	}
	

	return res;
}

List<Job*>* job_search_skill(Worker *w, List<Job*> *j, std::string zip_code)
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

List<Job*>* job_search_cmp(List<Job*> *j, Company *c)
{
	List<Job*>* res = new List<Job*>;
	Node<Job*>* cur = j->first;

	while(cur){
		if(cur->data->company == c){
			res->addlast(cur->data);
		}
		cur = cur->next;
	}

	return res;
}
