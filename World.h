#pragma once

#include <vector>

#include "Train.h"
#include "Station.h"

class World
{
	std::vector<std::shared_ptr<Station>> stations;
	std::vector<std::shared_ptr<Train>> trains;

	//names of stations
	std::vector<std::string> stnames;

	//ever-incrementing number for trains ID
	int idnum;

public:

	World();

	void Write();

	void simulate();

	void moveTrain(std::shared_ptr<Train> trn);

	void operator()()
	{
		simulate();
	}

	void listTrains();

	void newTrain(short dir, std::string name);
};
