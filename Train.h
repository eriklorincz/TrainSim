#pragma once

#include <memory>
#include <string>

class Place;

class Train
{
	int ID;
	std::shared_ptr<Place> place;
	short dir; //direction of the train  0 : left to right; 1: right to left
	std::string startName; //name of the starting station

public:

	Train(int id, short dr, std::string sn) : ID{ id }, dir{ dr }, startName { sn }
	{

	}

	int getID()
	{
		return ID;
	}

	std::shared_ptr<Place> getPlace()
	{
		return place;
	}

	void setPlace(std::shared_ptr<Place> newPlace)
	{
		place = newPlace;
	}

	short getDir()
	{
		return dir;
	}

	std::string getStart()
	{
		return startName;
	}
};
