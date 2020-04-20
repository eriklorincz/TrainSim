#include "pch.h"
#include <iostream>

#include "Train.h"
#include "Station.h"

int main()
{
	Train train1(9786);
    std::cout << train1.getID(); 

	Station Gyor("Gyor", 7);

	std::cout << Gyor.getName() << " allomason " << Gyor.getLines() << " vagany van";
}

