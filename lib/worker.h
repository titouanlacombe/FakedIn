#pragma once

#include "job.h"

class Worker
{
public:
	std::string first_name;
	std::string last_name;
	std::string email;
	std::string zip_code;
	List<std::string>* skills;
	List<Worker*>* colleagues;
	Company* company;

	Worker();
	Worker(std::string _first_name, std::string _last_name, std::string _email);
	~Worker();
	// rajoute une compétence a w
	void add_skill(std::string skill);
	// rajoute un collegue a w
	void add_colleague(Worker* colleague);
	// change le code postal de w
	void set_zip_code(std::string zip_code);
	// change l'entreprise de w
	void set_company(Company* company);
	// donne l'etat de w
	bool employed();
};
