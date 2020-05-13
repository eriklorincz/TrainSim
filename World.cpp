#include "pch.h"
#include "World.h"

#include <iostream>


World::World()
{
	Station Sopron("Sopron", 4);
	stations.push_back(Sopron);

	Station Fertoszentmiklos("Fertoszentmiklos", 4);
	stations.push_back(Fertoszentmiklos);

	Station Petohaza("Petohaza", 2);
	stations.push_back(Petohaza);

	Station Kapuvar("Kapuvar", 3);
	stations.push_back(Kapuvar);

	Station Szarfold("Szarfold", 1);
	stations.push_back(Szarfold);

	Station Rabatamasi("Rabatamasi", 2);
	stations.push_back(Rabatamasi);

	Station Farad("Farad", 1);
	stations.push_back(Farad);

	Station Csorna("Csorna", 3);
	stations.push_back(Csorna);

	Station Kony("Kony", 2);
	stations.push_back(Kony);

	Station Enese("Enese", 2);
	stations.push_back(Enese);

	Station Rabapatona("Rabapatona", 1);
	stations.push_back(Rabapatona);

	Station Ikreny("Ikreny", 2);
	stations.push_back(Ikreny);

	Station Gyor("Gyor", 2);
	stations.push_back(Gyor);
}

void World::Write()
{
	for (auto i : stations)
	{
		std::cout << i.getName() << " station has " << i.getPlatforms() << " platforms" << std::endl;
	}
}
