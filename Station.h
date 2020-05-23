#pragma once
#include <string>
#include <memory>

#include <optional>

class Train;

//abstract class for interface use
class Place
{
protected:

	std::shared_ptr<Place> next;
	std::shared_ptr<Place> previous;

	std::optional<std::shared_ptr<Train>> train;

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

	virtual void trainArrived(std::shared_ptr<Train> trn)
	{
		train = trn;
	}

	virtual void trainDeparts()
	{
		train.reset();
	}

	virtual bool trainPresent()
	{
		if (train)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

//Fragments of the distance between stations
class Railway final : public Place
{
public:
	Railway(std::shared_ptr<Place> n, std::shared_ptr<Place> p) : Place{ n, p }
	{

	}

	std::string print() override
	{
		if (train)
		{
			if (train.value()->getDir() == 1)
			{
				return "K";
			}
			return "T";
		}
		else
		{
			return "-";
		}
	}
};

//Stations, where trains will stop by schedule or to wait for other trains
class Station final : public Place
{

private:
	std::string name;
	int platforms;


public:
	Station(std::shared_ptr<Place> n, std::shared_ptr<Place> p, std::string nm, int plat) : Place{ n, p }, name{ nm }, platforms{ plat }
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
