#include "network.h"

Network::Network()
{

}

Network::~Network()
{

}

int Network::size()
{
	return workers->length;
}

bool Network::linked(Worker *a, Worker *b)
{
	return false;
}
