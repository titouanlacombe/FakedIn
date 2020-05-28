#pragma once

#include "data_base.h"

class Network
{
public:
	List<Worker*>* workers;

	Network();
	~Network();

	//retourne la taille du Network
	int size();
	//determine s'il existe une chaine de collegues entre deux travailleurs
	bool linked(Worker *a, Worker *b);
};
