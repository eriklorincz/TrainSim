#include "pch.h"
#include "World.h"
#include "Train.h"

#include <iostream>
#include <string>
#include <memory>
#include <fstream>

using namespace std;

World::World()
{
	string station_name;
	int station_platforms;
	int time_between;
	std::shared_ptr<Place> temp = nullptr;

	ifstream ReadFile("StationList.txt");

	//read the station parameters from the given file, and set up the World
	int counter = 0;
	while (ReadFile >> station_name >> time_between >> station_platforms)
	{
		//create a new station dynamically 
		stations.push_back(std::make_shared<Station>(nullptr, temp, station_name, station_platforms));

		if (counter != 0)
		{
			temp->setNext(stations[counter]);
		}
		
		//create as many Railway parts, as time is needed (in minutes) to get to the next station
		temp = stations[counter];
		for (int i = 0; i < time_between; i++)
		{
			temp->setNext(std::make_shared<Railway>(nullptr, temp));
			temp = temp->getNext();
		}

		counter++;
	}


	ReadFile.close();

	simulate();
}

void World::Write()
{
	cout << endl;
	//checking if everything is OK
	/*for (auto i : stations)
	{
		cout << i->getName() << " station has " << i->getPlatforms() << " platforms" << endl;
	}
	cout << endl;*/

	//Basic visualization of the world, may change with time or be completely removed
	shared_ptr<Place>iter = stations[0];

	while (iter != nullptr)
	{
		cout << iter->print();
		iter = iter->getNext();
	}

	cout << endl;
	cout << endl;


	/*while (iter != nullptr)
	{
		auto variable = dynamic_pointer_cast<Station>(iter);

		if (variable)
		{
			cout << variable->getName();
		}
		else
		{
			cout << "-";
		}
		iter = iter->getNext();
	}*/
}

void World::simulate()
{
	auto train1 = std::make_shared<Train>(0);
	train1->setPlace(stations[0]);

	while (train1->getPlace() != stations[stations.size()-1])
	{
		train1->getPlace()->trainDeparts();
		train1->setPlace(train1->getPlace()->getNext());
		train1->getPlace()->trainArrived(train1);

		Write();

		
	}

}
