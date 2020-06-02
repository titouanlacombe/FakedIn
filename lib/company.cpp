#include "company.h"

Company::Company()
{
	email = "";
  zip_code = "";
  name = "";
}

Company::Company(std::string _name, std::string _zip_code, std::string _email)
{
	email = _email;
  zip_code = _zip_code;
  name = _name;
}

Company::~Company()
{
  
}

bool operator==(Company& l, Company& r)
{
	return l.name == r.name;
}

bool operator!=(Company& l, Company& r)
{
	return !(l==r);
}

std::ostream& operator<<(std::ostream& os, const Company& c)
{
	os << "Entreprise: " << c.name << " Code postal: " << c.zip_code << " email: " << c.email;
	return os;
}

Company* srch_cmp_list(List<Company*>& companies, std::string name)
{
	Company* c = NULL;
	auto it = companies.begin();

	while (it != companies.end() && c == NULL)
	{
		if ((*it)->name == name) c = *it;
		it++;
	}
	return c;
}

bool cmp_exist(List<Company*>& companies, std::string name)
{
	return srch_cmp_list(companies, name) != NULL;
}

void load_cmp()
{
	return;
}
