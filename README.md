# TrainSim
 University Project for C++ course
 
## The project
The program "simulates" a railway track. Trains are moving in both directions. Letter "T" marks a train that is going from left to right, letter "K" marks one going the other direction. In the beginning of every hour, new trains started from the two ends of the track. Trains can evade each other on stations, only one train is allowed on one line at a time. The user can type in commands to view or modify actual state. 

The simulation is "minute" based, one cycle means one minute in "real life". The speed can be changed from the code (World.cpp, line 133).

## How to use
For just watching the simulation, it is recommended to speed up the program by lowering the number of seconds the thread would sleep (World.cpp, line 133).

For testing user commands, it is recommended to comment out the Write() method in World.cpp, line 131. This way, the current state isn't printed out in each step, (but that can be done via user command if needed), so it won't interfere with the characters of the typed command. 

The uploaded version refreshes every 5 seconds, and prints out the current state every time.

## User commands
* exit - quit the program
* write - print the content of the world (simply calls Write())
* list - write information of the currently running trains
* newtrain - start a new train from selected station and direction. Follow on-screen instructions

## Used elements
* threads - one thread for handling user input, other for doing everything else
* uniform initialization 
* foreach iteration
* shared pointers
* chrono
* exception
* final keyword
* std::optional

### Final notes
* In the final version there is no use for platform numbers on stations
* System("cls") could be used, so only the current state would be visible, like in a real simulation. I left it out so changes can be followed easily. 
* Any real or imagined track can be used by the program through "StationList.txt".

   The pattern: StationName {Space} MinutesToNextStation(int) {Space} NumberOfPlatforms(int)
