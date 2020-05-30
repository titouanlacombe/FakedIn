#include "UI.h"

int load_modules()
{
	load_wrk();
	load_list();
	load_cmp();
	load_job();
	load_wrk();
	load_db();
	load_srch();
	load_UI();

	return 0;
}

int main(void)
{
	List<Company*> companies;
	List<Job*> jobs;
	List<Worker*> workers;

	load_modules();

	log_begin();
	load(&companies, &jobs, &workers, "app/data_base");
	init_lists(&companies, &jobs, &workers);
	std::cout << ASCII_ART << std::endl;

	home();

	std::cout << "Merci de votre visite !" << std::endl;
	save(&companies, &jobs, &workers, "app/data_base");
	log_end();

	return 0;
}
