#pragma once
#include <string>
#include <memory>

class Train;

//abstract class for interface use
class Place
{
protected:

	std::shared_ptr<Place> next;
	std::shared_ptr<Place> previous;

	std::shared_ptr<Train> train;

public:
	Place(std::shared_ptr<Place> n, std::shared_ptr<Place> p) : next {n}, previous {p}
	{

	}

	virtual ~Place() = default;
	 

	virtual std::string print() = 0;

	std::shared_ptr<Place> getNext()
	{
		return next;
	}

	std::shared_ptr<Place> getPrev()
	{
		return previous;
	}

	void setNext(std::shared_ptr<Place> n)
	{
		next = n;
	}

	void setPrev(std::shared_ptr<Place> p)
	{
		previous = p;
	}

	void trainArrived(std::shared_ptr<Train> trn)
	{
		train = trn;
	}

	void trainDeparts()
	{
		train.reset();
	}

};

//Fragments of the distance between stations
class Railway : public Place
{
public:
	Railway(std::shared_ptr<Place> n, std::shared_ptr<Place> p) : Place{ n, p }
	{

	}

	std::string print() override
	{
		if (train)
		{
			return "T";
		}
		else
		{
			return "-";
		}
	}
};

//Stations, where trains will stop by schedule or to wait for other trains
class Station : public Place
{

private:
	std::string name;
	int platforms;


public:
	Station(std::shared_ptr<Place> n, std::shared_ptr<Place> p, std::string nm, int plat) : Place{n, p}, name { nm }, platforms{ plat }
	{

	}

	int getPlatforms()
	{
		return platforms;
	}
	
	std::string getName()
	{
		return name;
	}

	std::string print() override
	{
		return name;
	}
};
