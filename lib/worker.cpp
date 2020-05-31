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

std::ostream& operator<<(std::ostream& os, const Worker& w)
{
	if (w.employed()) os << "Employé: ";
	else os << "Chercheur d'emploi: ";
	os << w.first_name << " " << w.last_name;
	if (w.employed()) os << ", Employé a: " << w.company->name;
	os << ", Compétences: ";
	auto tmp = w.skills->first;
	while (tmp != w.skills->last)
	{
		os << tmp->data << ", ";
		tmp = tmp->next;
	}
	os << tmp->data;
	return os;
}

Worker* srch_wrk_list(List<Worker*>* workers, std::string first_name, std::string last_name)
{
	Worker* w;
	auto cur = workers->first;

	while (cur != NULL)
	{
		if (cur->data->first_name == first_name && cur->data->last_name == last_name) w = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return w;
}

List<Worker*>* company_employees(List<Worker*>* workers, Company* c)
{
	List<Worker*>* l = new List<Worker*>;
	auto tmp = workers->first;
	while (tmp != NULL)
	{
		if (tmp->data->company == c) l->addlast(tmp->data);
	}
	return l;
}

void load_wrk()
{
	return;
}
