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

Job::~Job() {return;}

void Job::add_skill(std::string skill) {skills.addlast(skill);}

bool operator==(Job& l, Job& r) {return l.title == r.title && l.company == r.company;}

bool operator!=(Job& l, Job& r) {return !(l==r);}

std::ostream& operator<<(std::ostream& os, const Job& j)
{
	os << j.title << " chez " << j.company->name << " (email: "
	<< j.company->email << ", Code postal: " << j.company->zip_code << ")";
	// auto it = j.skills->first;
	// os << " Compétences requises: ";
	// while (it != j.skills->last)
	// {
	// 	os << it->data << ", ";
	// 	it = it->next;
	// }
	// os << it->data;
	return os;
}

List<Job*>* company_jobs(List<Job*>& jobs, Company& c)
{
	List<Job*>* l = new List<Job*>();
	auto it = jobs.first();
	while (it != jobs.end())
	{
		if (*(*it)->company == c) l->addlast(*it);
		it++;
	}
	return l;
}

Job* srch_job_list(List<Job*>& jobs, Company& c, std::string title)
{
	Job* j = NULL;
	auto it = jobs.first();
	while (it != jobs.end() && j == NULL)
	{
		if ((*it)->title == title && *(*it)->company == c) j = *it;
		it++;
	}
	return j;
}

bool job_exist(List<Job*>& jobs, Company& c, std::string title) {return srch_job_list(jobs, c, title) != NULL;}
