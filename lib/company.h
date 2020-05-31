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

void load_cmp();
