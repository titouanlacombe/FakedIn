#pragma once

#include "company.h"

class Job
{
public:
	std::string name;
	List<std::string>* skills;
	Company* company;

	Job();
	Job(std::string _name, List<std::string>* _skills, Company* _company);
	~Job();
};
