#include "job.h"

Job::Job()
{
  title = "";
  company = NULL;
  skills = List<std::string>();
}

Job::Job(std::string _title, Company* _company)
{
  title = _title;
  company = _company;
  skills = List<std::string>();
}

Job::~Job()
{
	return;
}

void Job::add_skill(std::string skill)
{
	skills.addlast(skill);
}

bool operator==(Job& l, Job& r)
{
	return l.title == r.title && l.company == r.company;
}

bool operator!=(Job& l, Job& r)
{
	return !(l==r);
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

List<Job*>* company_jobs(List<Job*>& jobs, Company& c)
{
	List<Job*>* l = new List<Job*>();
	auto tmp = jobs.begin();
	while (tmp != jobs.end())
	{
		if (*(*tmp)->company == c) l->addlast(*tmp);
		tmp++;
	}
	return l;
}

Job* srch_job_list(List<Job*>& jobs, Company& c, std::string title)
{
	Job* j = NULL;
	auto it = jobs.begin();
	while (it != jobs.end() && j == NULL)
	{
		if ((*it)->title == title && *(*it)->company == c) j = *it;
		it++;
	}
	return j;
}

bool job_exist(List<Job*>& jobs, Company& c, std::string title)
{
	return srch_job_list(jobs, c, title) != NULL;
}

void load_job()
{
	return;
}
