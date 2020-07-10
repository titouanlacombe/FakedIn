#include "mylog.h"
#include "data_base.h"
#include "UI.h"

#include <iostream>

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

int main(void)
{
	log_begin("app/logs");
	log_write("App start");

	load("app/data_base");

	std::cout << ASCII_ART << std::endl;
	std::cout << "=== Bienvenu sur FakedIn ! L'application qui réalise vos rêves ===" << std::endl;

	home();

	std::cout << "Merci de votre visite !" << std::endl;

	save("app/data_base");
	
	log_write("App quit");
	log_end();

	return 0;
}
