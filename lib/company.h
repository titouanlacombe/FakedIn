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
};

void load_cmp();