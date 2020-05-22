#pragma once

#include <vector>

#include "Train.h"
#include "Station.h"

class World
{
	std::vector<std::shared_ptr<Station>> stations;
	std::vector<std::shared_ptr<Train>> trains;

public:

	World();

	void Write();

	void simulate();

	void moveTrain(std::shared_ptr<Train> trn);
};
