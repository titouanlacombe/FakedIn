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
};

void load_job();