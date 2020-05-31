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

std::ostream& operator<<(std::ostream& os, const Company& c)
{
	os << "Entreprise: " << c.name << " Code postal: " << c.zip_code << " email: " << c.email;
	return os;
}

Company* srch_cmp_list(List<Company*>* companies, std::string name)
{
	Company* c;
	auto cur = companies->first;

	while (cur != NULL)
	{
		std::cout << name << " " << cur->data->name << std::endl;
		if (cur->data->name == name) c = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return c;
}

void load_cmp()
{
	return;
}
