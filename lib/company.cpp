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
