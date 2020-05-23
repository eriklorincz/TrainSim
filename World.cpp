#include "pch.h"
#include "World.h"
#include "Train.h"

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

World::World() : idnum {0}
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

		stnames.push_back(station_name);

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

}

void World::Write()
{
	cout << endl;
	//checking if everything is OK    For debugging, use when there is problem with file reading
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

	while (true)
	{
		//starting trains every hour
		if (i % 60 == 0)
		{
			auto train1 = make_shared<Train>(idnum, 0, stations[0]->getName());
			train1->setPlace(stations[0]);
			trains.push_back(train1);

			train1.reset();

			train1 = std::make_shared<Train>(idnum + 1, 1, stations[stations.size()-1]->getName());
			train1->setPlace(stations[stations.size() - 1]);
			trains.push_back(train1);

			train1.reset();

			idnum += 2;
		}

		
		for (auto train : trains)
		{
			moveTrain(train);
		}

		//deleting trains that have arrived to the opposite final destination
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
		this_thread::sleep_for(chrono::seconds(5));
	}
}

//step one place with the train in the direction (if possible)
void World::moveTrain(std::shared_ptr<Train> trn)
{

	//left to right
	if (trn->getDir() == 0)
	{

		//testing for other trains on track
		auto test1 = dynamic_pointer_cast<Station> (trn->getPlace());

		if (test1)
		{
			auto test2 = trn->getPlace();
			do
			{
				test2 = test2->getNext();

				test1 = dynamic_pointer_cast<Station> (test2);

				if (test1)
				{
					break;
				}


				if (test2 && test2->trainPresent())
				{
					return;
				}


			} while (!test1);
		}

		trn->getPlace()->trainDeparts();
		trn->setPlace(trn->getPlace()->getNext());
		trn->getPlace()->trainArrived(trn);
	}
	//right to left
	else
	{
		//testing for other trains on track
		auto test1 = dynamic_pointer_cast<Station> (trn->getPlace());

		if (test1)
		{

			auto test2 = trn->getPlace();
			do
			{
				test2 = test2->getPrev();

				test1 = dynamic_pointer_cast<Station> (test2);

				if (test1)
				{
					break;
				}


				if (test2 && test2->trainPresent())
				{
					return;
				}
				test1 = dynamic_pointer_cast<Station> (test2);

			} while (!test1);
		}

		trn->getPlace()->trainDeparts();
		trn->setPlace(trn->getPlace()->getPrev());
		trn->getPlace()->trainArrived(trn);
	}
}

//printing train parameters / valuable informations to the screen
void World::listTrains()
{
	for (auto train : trains)
	{
		auto test1 = dynamic_pointer_cast<Station> (train->getPlace());
		cout << "Train number " << train->getID() << " started from " << train->getStart();

		//if on a station
		if (test1)
		{
			cout << " is on station " << test1->getName();

			if (train->getDir() == 0)
			{
				if (test1 == stations[stations.size() - 1])
				{
					cout << ", Final destination\n";
					continue;
				}

			}
			else
			{
				if (test1 == stations[0])
				{
					cout << ", Final destination\n";
					continue;
				}
			}
			
		}
		else
		{
			cout << " is on the move,";
		}				
		//left to right
		if (train->getDir() == 0)
		{
			int minutes = 1;
			auto test2 = train->getPlace()->getNext();
			bool written = false;

			test1 = dynamic_pointer_cast<Station>(test2);

			while (test1 != stations[stations.size() - 1])
			{
				if (test1 && !written)
				{
					cout << " arriving to station " << test1->getName() << " in " << minutes << " minutes,";
					written = true;
				}
				minutes++;
				test2 = test2->getNext();
				test1 = dynamic_pointer_cast<Station>(test2);
			}
			cout << " final destination " << stations[stations.size() - 1]->getName() << " in " << minutes << " minutes" << endl;
		}
		//right to left
		else
		{
			int minutes = 1;
			auto test2 = train->getPlace()->getPrev();
			bool written = false;

			test1 = dynamic_pointer_cast<Station>(test2);

			while (test1 != stations[0])
			{
				if (test1 && !written)
				{
					cout << " arriving to station " << test1->getName() << " in " << minutes << " minutes,";
					written = true;
				}
				minutes++;
				test2 = test2->getPrev();
				test1 = dynamic_pointer_cast<Station>(test2);
			}
			cout << " final destination " << stations[0]->getName() << " in " << minutes << " minutes" << endl;
		}

	}
}

//start a new train from specified station (user command only)
void World::newTrain(short dir, std::string name)
{
	int i = 0;
	while (i < stnames.size()  && stnames[i] != name)
	{
		i++;
	}
	
	if (i == stnames.size() )
	{
		cout << "No such station\n";
		return;
	}

	if (i == stnames.size() - 1 && dir == 0)
	{
		cout << "No way there\n";
		return;
	}

	if (i == 0 && dir == 1)
	{
		cout << "No way there\n";
		return;
	}

	auto train1 = make_shared<Train>(idnum, dir, stnames[i]);
	train1->setPlace(stations[i]);
	trains.push_back(train1);

	train1.reset();
	idnum++;
}
