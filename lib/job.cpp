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

void load_job()
{
	return;
}
