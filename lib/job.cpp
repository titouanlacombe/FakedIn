#include "job.h"

Job::Job()
{
  title = "";
  company = NULL;
  skills = NULL;

}

Job::Job(std::string _title, List<std::string>* _skills, Company* _company)
{
  title = _title;
  skills = _skills;
  company = _company;
}

Job::~Job()
{

}

std::ostream& operator<<(std::ostream& os, const Job& j)
{
	os << "Offre d'emploi: " << j.title << ", Entreprise: " << j.company->name << ", Compétences requises: ";
	auto tmp = j.skills->first;
	while (tmp != j.skills->last)
	{
		os << tmp->data << ", ";
		tmp = tmp->next;
	}
	os << tmp->data;
	return os;
}

List<Job*>* company_jobs(List<Job*>* jobs, Company* c)
{
	List<Job*>* l = new List<Job*>;
	auto tmp = jobs->first;
	while (tmp != NULL)
	{
		if (tmp->data->company == c) l->addlast(tmp->data);
	}
	return l;
}

void load_job()
{
	return;
}
