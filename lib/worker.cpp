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
	auto tmp = colleagues->first;
	while(tmp != NULL)
	{
		colleagues->first->data->colleagues->remove(this);
		tmp = tmp->next;
	}
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

bool Worker::employed()
{
	return company != NULL;
}
