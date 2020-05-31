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
	os << "Offre d'emploi: " << j.title << " a " << j.company->name << "(email: "
	<< j.company->email << " Code postal: " << j.company->zip_code << ")";
	// auto tmp = j.skills->first;
	// os << " Compétences requises: ";
	// while (tmp != j.skills->last)
	// {
	// 	os << tmp->data << ", ";
	// 	tmp = tmp->next;
	// }
	// os << tmp->data;
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

Job* srch_job_list(List<Job*>* jobs, Company* c, std::string title)
{
	Job* j;
	auto cur = jobs->first;

	while (cur != NULL)
	{
		if (cur->data->title == title && cur->data->company == c) j = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return j;
}

void load_job()
{
	return;
}
