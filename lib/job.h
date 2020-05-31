#pragma once

#include "company.h"

class Job
{
public:
	std::string title;
	List<std::string>* skills;
	Company* company;

	Job();
	Job(std::string _title, List<std::string>* _skills, Company* _company);
	~Job();
	friend std::ostream& operator<<(std::ostream& os, const Job& j);
};

// Rechercher un job à partir d'un titre et d'une companie
Job* srch_job_list(List<Job*>* jobs, Company* c, std::string title);

List<Job*>* company_jobs(List<Job*>* jobs, Company* c);

void load_job();
