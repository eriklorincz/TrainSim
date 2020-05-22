#include "pch.h"
#include "World.h"
#include "Train.h"

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <algorithm>

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
}

void World::simulate()
{
	int i = 0;
	int idnum = 0;

	while (i < 200)
	{
		if (i % 60 == 0)
		{
			auto train1 = make_shared<Train>(idnum, 0);
			train1->setPlace(stations[0]);
			trains.push_back(train1);

			train1.reset();

			train1 = std::make_shared<Train>(idnum + 1, 1);
			train1->setPlace(stations[stations.size() - 1]);
			trains.push_back(train1);

			train1.reset();

			idnum += 2;
		}

		
		for (auto train : trains)
		{
			moveTrain(train);
		}

		//deleting trains that are arrived to the opposite final destination
		for (int j = 0; j < trains.size(); j++)
		{
			if (trains[j]->getDir() == 0)
			{
				if (trains[j]->getPlace()->getNext() == nullptr)
				{
					trains[j].reset();
					trains.erase(trains.begin() + j);
					j--;
				}
			}
			else
			{
				if (trains[j]->getPlace()->getPrev() == nullptr)
				{
					trains[j].reset();
					trains.erase(trains.begin() + j);
					j--;
				}
			}

		}

		Write();
		i++;
	}

}

//step one place with the train in the direction
void World::moveTrain(std::shared_ptr<Train> trn)
{
	trn->getPlace()->trainDeparts();

	if (trn->getDir() == 0)
	{
		trn->setPlace(trn->getPlace()->getNext());
		trn->getPlace()->trainArrived(trn);
	}
	else
	{
		trn->setPlace(trn->getPlace()->getPrev());
		trn->getPlace()->trainArrived(trn);
	}

}
