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
	load_language("./languages/english.lang");

	std::cout << ASCII_ART << std::endl;
	std::cout << "=== " + get_phrase(104) + " ===" << std::endl;

	home();

	std::cout << get_phrase(105) << std::endl;

	save("app/data_base");
	
	log_write("App quit");
	log_end();

	return 0;
}
