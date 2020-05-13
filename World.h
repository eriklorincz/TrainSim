#pragma once

#include <vector>

#include "Train.h"
#include "Station.h"

class World
{
	std::vector<Station> stations;

public:

	World();

	void Write();
};
