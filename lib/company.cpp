#include "company.h"

List<Company*> companies_list;

Company::Company()
{
	email = "";
  zip_code = "";
  name = "";
	companies_list.addlast(this);
}

Company::Company(std::string _name, std::string _zip_code, std::string _email)
{
	email = _email;
  zip_code = _zip_code;
  name = _name;
	companies_list.addlast(this);
}

Company::~Company()
{
	companies_list.remove(this);
}

bool operator==(Company& l, Company& r) {return l.name == r.name;}

bool operator!=(Company& l, Company& r) {return !(l==r);}

std::ostream& operator<<(std::ostream& os, const Company& c)
{
	os << "Entreprise: " << c.name << " Code postal: " << c.zip_code << " email: " << c.email;
	return os;
}

Company* get_company(std::string name)
{
	Company* c = NULL;
	auto it = companies_list.first();
	while (it != companies_list.end() && c == NULL)
	{
		if ((*it)->name == name) c = *it;
		it++;
	}
	return c;
}

Company* get_company(int id) {return companies_list[id];}

bool cmp_exist(std::string name) {return get_company(name) != NULL;}

List<Company*>& get_companies() {return companies_list;}
