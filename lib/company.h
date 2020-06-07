#pragma once

#include "list.h"

class Company
{
public:
	std::string name; // Name of the company
	std::string zip_code;  // Zip code of the company
	std::string email;  // email of the company

	Company();
	Company(std::string _name, std::string _zip_code, std::string _email);
	~Company();
	friend bool operator==(Company& l, Company& r); // Returns true if l&r have the same name
	friend bool operator!=(Company& l, Company& r); // Returns (!l==r)
	friend std::ostream& operator<<(std::ostream& os, const Company& c); // Used to print the company in the console
};

// Search a company by it's name
Company* srch_cmp_list(List<Company*>& companies, std::string name);

// Search if a company with the name 'name' already exist in companies
bool cmp_exist(List<Company*>& companies, std::string name);
