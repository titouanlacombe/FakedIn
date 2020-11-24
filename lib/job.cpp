#include "job.h"

List<Job>* job_list = NULL;

Job::Job(std::string _title, Company* _company)
{
	title = _title;
	company = _company;
	skills = List<std::string>();
	
	if (!job_list) job_list = new List<Job>();
	job_list->addlast(this);
}

Job::Job() {Job("", NULL);}

Job::~Job() {job_list->remove(this);}

void Job::add_skill(std::string skill) {skills.addlast(new std::string(skill));}

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

List<Job>* company_jobs(Company& c)
{
	List<Job>* l = new List<Job>();
	auto it = job_list->first();
	while (it != job_list->end())
	{
		if (*(*it)->company == c) l->addlast(*it);
		it++;
	}
	return l;
}

Job* get_job(Company& c, std::string title)
{
	Job* j = NULL;
	auto it = job_list->first();
	while (it != job_list->end() && j == NULL)
	{
		if ((*it)->title == title && *(*it)->company == c) j = *it;
		it++;
	}
	return j;
}

bool job_exist(Company& c, std::string title) {return get_job(c, title) != NULL;}

List<Job>* get_jobs() {return job_list;}
