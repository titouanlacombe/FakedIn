#include "job.h"

Job::Job()
{
  name = "";
  company = NULL;
  skills = NULL;

}

Job::Job(std::string _name, List<std::string>* _skills, Company* _company)
{
  name = _name;
  skills = _skills;
  company = _company;
}

Job::~Job()
{

}
