#include <iostream>

#include "UI.h"

int main(void)
{
	log_begin();
	load(companies, jobs, workers, "data_base");
	std::cout << ASCII_ART << std::endl;

	home();

	std::cout << "Merci de votre visite !" << std::endl;
	save(companies, jobs, workers, "data_base");
	log_end();

	return 0;
}
