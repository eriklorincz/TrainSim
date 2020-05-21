#pragma once

#include <memory>

class Place;

class Train
{
	int ID;
	std::shared_ptr<Place> place;

public:

	Train(int id) : ID{ id }
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
};
