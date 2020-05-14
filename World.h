#pragma once

#include <vector>

#include "Train.h"
#include "Station.h"

class World
{
	std::vector<std::shared_ptr<Station>> stations;

public:

	World();

	void Write();
};
