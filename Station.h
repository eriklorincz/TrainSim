#pragma once
#include <string>

class Station
{
	std::string name;
	int platforms;

public:
	Station(std::string nm, int plat) : name{ nm }, platforms{ plat }
	{

	}

	int getPlatforms()
	{
		return platforms;
	}
	
	std::string getName()
	{
		return name;
	}
};
