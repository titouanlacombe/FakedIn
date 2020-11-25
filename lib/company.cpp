#include "company.h"

List<Company>* companies_list = NULL;

Company::Company(std::string _name, std::string _zip_code, std::string _email)
{
	email = _email;
 	zip_code = _zip_code;
 	name = _name;
	
	if (!companies_list) companies_list = new List<Company>();
	companies_list->addlast(this);
}

Company::Company() {Company("", "", "");}

Company::~Company() {companies_list->remove(this);}

bool operator==(Company& l, Company& r) {return l.name == r.name;}

bool operator!=(Company& l, Company& r) {return !(l==r);}

std::ostream& operator<<(std::ostream& os, const Company& c)
{
	os << get_phrase(90) + ": " << c.name << " " + get_phrase(89) + ": " << c.zip_code << " " + get_phrase(88) + ": " << c.email;
	return os;
}

Company* get_company(std::string name)
{
	if (name.empty()) return NULL;
	
	Company* c = NULL;
	auto it = companies_list->first();
	while (it != companies_list->end() && c == NULL)
	{
		if ((*it)->name == name) c = *it;
		it++;
	}
	return c;
}

bool cmp_exist(std::string name) {return get_company(name) != NULL;}

List<Company>* get_companies() {return companies_list;}
