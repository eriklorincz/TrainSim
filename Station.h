#pragma once
#include <string>

class Station
{
	std::string name;
	int lines;

public:
	Station(std::string nm, int lin) : name{ nm }, lines{ lin }
	{

	}

	int getLines()
	{
		return lines;
	}
	
	std::string getName()
	{
		return name;
	}
};
