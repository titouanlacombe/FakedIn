#include "worker.h"

Worker::Worker()
{
	first_name = "";
	last_name = "";
	email = "";
	zip_code = "";
	skills = NULL;
	colleagues = NULL;
	company = NULL;
}

Worker::Worker(std::string _first_name, std::string _last_name, std::string _email)
{
	first_name = _first_name;
	last_name = _last_name;
	email = _email;
	zip_code = "";
	skills = new List<std::string>();
	colleagues = new List<Worker*>();
	company = NULL;
}

Worker::~Worker()
{
	delete skills;
	delete colleagues;
}

void Worker::add_skill(std::string skill)
{
	skills->addlast(skill);
}

void Worker::add_colleague(Worker* colleague)
{
	colleagues->addlast(colleague);
}

void Worker::set_zip_code(std::string _zip_code)
{
	zip_code = _zip_code;
}

void Worker::set_company(Company* _company)
{
	company = _company;
}

bool Worker::employed() const
{
	return company != NULL;
}

void Worker::remove_from_coll()
{
	auto tmp = colleagues->first;
	while(tmp != NULL)
	{
		colleagues->first->data->colleagues->remove(this);
		tmp = tmp->next;
	}
}

bool operator==(Worker& l, Worker& r)
{
	return l.first_name == r.first_name && l.last_name == r.last_name;
}

bool operator!=(Worker& l, Worker& r)
{
	return !(l==r);
}

std::ostream& operator<<(std::ostream& os, const Worker& w)
{
	os << w.first_name << " " << w.last_name << " email: " << w.email;
	if (w.employed()) os << " employé a: " << w.company->name;
	// os << ", Compétences: ";
	// auto tmp = w.skills->first;
	// while (tmp != w.skills->last)
	// {
	// 	os << tmp->data << ", ";
	// 	tmp = tmp->next;
	// }
	// os << tmp->data;
	return os;
}

Worker* srch_wrk_list(List<Worker*>* workers, std::string first_name, std::string last_name)
{
	Worker* w = NULL;
	auto cur = workers->first;

	while (cur != NULL && w == NULL)
	{
		if (cur->data->first_name == first_name && cur->data->last_name == last_name) w = cur->data;
		cur = cur->next;
	}
	return w;
}

bool wrk_exist(List<Worker*>* workers, std::string first_name, std::string last_name)
{
	return srch_wrk_list(workers, first_name, last_name) != NULL;
}

List<Worker*>* company_employees(List<Worker*>* workers, Company* c)
{
	List<Worker*>* l = new List<Worker*>;
	auto tmp = workers->first;
	while (tmp != NULL)
	{
		if (tmp->data->company == c) l->addlast(tmp->data);
		tmp = tmp->next;
	}
	return l;
}

void load_wrk()
{
	return;
}
