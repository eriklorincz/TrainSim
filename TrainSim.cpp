//Author: Lõrincz Erik
//University project for C++ course
//simulating a railway track

#include "pch.h"
#include <iostream>
#include <thread>

#include "World.h"

using namespace std;

//callable function for the input thread
void input(World& wrld)
{
	while (true)
	{
		string command;
		cin >> command;

		if (command == "exit")
		{
			break;
		}
		else if (command == "write")  //print the world content
		{
			wrld.Write();
		}
		else if (command == "list")  //show information about running trains
		{
			wrld.listTrains();
		}
		else if (command == "newtrain")
		{
			string name;
			string sdir;

			cout << "Give name of the starting station!\n";
			cin >> name;
			cout << "Give direction ( 0: left to right, 1: right to left)\n";
			cin >> sdir;

			try
			{
				short dir = stoi(sdir);
				
				if (dir == 0 || dir == 1)
				{
					wrld.newTrain(dir, name);
				}
				else
				{
					cout << "Wrong number\n";
				}
				
			}
			catch (exception & err)
			{
				cout << "Invalid direction\n";
			}


			
		}
	}
}

int main()
{
	World world;

	thread th1(ref(world));

	thread inpthread(input ,ref(world));

	th1.detach();
	inpthread.join();

}

