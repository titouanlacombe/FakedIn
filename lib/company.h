#pragma once

#include "list.h"

class Company
{
public:
	std::string name;
	std::string zip_code;
	std::string email;

	Company();
	Company(std::string _name, std::string _zip_code, std::string _email);
	~Company();
	friend std::ostream& operator<<(std::ostream& os, const Company& c);
};

// Recherche d'une companie par son nom
Company* srch_cmp_list(List<Company*>* companies, std::string name);

// Recherche si une companie existe déjà
bool cmp_exist(List<Company*>* companies, std::string name);

void load_cmp();
