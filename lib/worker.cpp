#include "worker.h"
#include "mylog.h"

List<Worker>* worker_list = NULL;

Worker::Worker(std::string _first_name, std::string _last_name, std::string _email)
{
	first_name = _first_name;
	last_name = _last_name;
	email = _email;
	zip_code = "";
	skills = List<std::string>();
	co_workers = List<Worker>();
	company = NULL;

	if (!worker_list) worker_list = new List<Worker>();
	worker_list->addlast(this);
}

Worker::Worker(std::string full_name, std::string _email)
{
	std::string _first_name;
	mygetline(full_name, _first_name, ' ');
	Worker(_first_name, full_name, _email);
}

Worker::Worker() {Worker("", "");}

Worker::~Worker() {worker_list->remove(this);}

void Worker::add_skill(std::string skill) {skills.addlast(new std::string(skill));}

void Worker::add_co_worker(Worker& co_worker) {co_workers.addlast(&co_worker);}

void Worker::set_zip_code(std::string _zip_code) {zip_code = _zip_code;}

void Worker::set_company(Company* _company) {company = _company;}

bool Worker::employed() const {return company != NULL;}

void Worker::remove_from_coll()
{
	auto it = co_workers.first();
	while(it != co_workers.end())
	{
		(*it)->co_workers.remove(this);
		it++;
	}
}

bool operator==(Worker& l, Worker& r) {return l.first_name == r.first_name && l.last_name == r.last_name;}

bool operator!=(Worker& l, Worker& r) {return !(l==r);}

std::ostream& operator<<(std::ostream& os, const Worker& w)
{
	os << w.first_name << " " << w.last_name << " (email: " << w.email;
	if (w.employed()) os << ", Travaille chez " << w.company->name;
	else os << ", Au chomage";
	os << ")";
	// os << ", Compétences: ";
	// auto it = w.skills->first;
	// while (it != w.skills->last)
	// {
	// 	os << it->data << ", ";
	// 	it = it->next;
	// }
	// os << it->data;
	return os;
}

Worker* get_worker(std::string first_name, std::string last_name)
{
	Worker* w = NULL;
	auto it = worker_list->first();
	while (it != worker_list->end() && w == NULL)
	{
		if ((*it)->first_name == first_name && (*it)->last_name == last_name) w = (*it);
		it++;
	}
	return w;
}

Worker* get_worker(std::string full_name)
{
	std::string first_name;
	mygetline(full_name, first_name, ' ');
	return get_worker(first_name, full_name);
}

bool wrk_exist(std::string first_name, std::string last_name) {return get_worker(first_name, last_name) != NULL;}

bool wrk_exist(std::string full_name) {return get_worker(full_name) != NULL;}

List<Worker>* company_employees(Company& c)
{
	List<Worker>* l = new List<Worker>();
	auto it = worker_list->first();
	while (it != worker_list->end())
	{
		if ((*it)->company != NULL && *(*it)->company == c) l->addlast(*it);
		it++;
	}
	return l;
}

List<Worker>* get_workers() {return worker_list;}
