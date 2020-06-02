#include "UI.h"

#define ASCII_ART															       \
"*********************************************   \n" \
"|     ______      __            ______      |   \n" \
"|    / ____/___ _/ /_____  ____/ /  _/___   |   \n" \
"|   / /_  / __ `/ //_/ _ \\/ __  // // __ \\  | \n" \
"|  / __/ / /_/ / ,< /  __/ /_/ // // / / /  |   \n" \
"| /_/    \\__,_/_/|_|\\___/\\__,_/___/_/ /_/   |\n" \
"|                                           |   \n" \
"| Made by: Lacombe, Billet, Veran           |   \n" \
"| Polytech Marseille - Informatique 3A      |   \n" \
"*********************************************   \n" 

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

	log_begin("app/logs");
	log_write("Start");

	load(companies, jobs, workers, "app/data_base");
	init_lists(companies, jobs, workers);

	std::cout << ASCII_ART << std::endl;
	std::cout << "=== Bienvenu sur FakedIn ! L'application qui réalise vos rêves ===" << std::endl;

	home();

	std::cout << "Merci de votre visite !" << std::endl;

	save(companies, jobs, workers, "app/data_base");
	
	log_write("Quitting...");
	log_end();

	return 0;
}
