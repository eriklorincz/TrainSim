#pragma once

#include <memory>

class Place;

class Train
{
	int ID;
	std::shared_ptr<Place> place;
	short dir; //direction of the train  0 : left to right; 1: right to left

public:

	Train(int id, short dr) : ID{ id }, dir{ dr }
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
};
