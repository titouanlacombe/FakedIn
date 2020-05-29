#include <iostream>

#include "UI.h"

int main(void)
{
	List<Company*> companies;
	List<Job*> jobs;
	List<Worker*> workers;

	log_begin();
	load(&companies, &jobs, &workers, "app/data_base");
	// init_lists(&companies, &jobs, &workers);
	std::cout << ASCII_ART << std::endl;

	home();

	std::cout << "Merci de votre visite !" << std::endl;
	save(&companies, &jobs, &workers, "app/data_base");
	log_end();

	return 0;
}
