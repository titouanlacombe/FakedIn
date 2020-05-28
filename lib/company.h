#pragma once

#include "list.h"

class Company
{
public:
	char* name;
	char* zip_code;
	char* email;

	Company();
	Company(char* _name, char* _zip_code, char* _email);
	~Company();
};
