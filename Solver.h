#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include "Bin.h"

class Solver
{
public:
	Solver(Bin* bin);
	~Solver();
	virtual int solve() =0;
	virtual std::string printResult() = 0;
	virtual std::string printShortResult() = 0;
	std::string printSolvedBoxes();
	void reset();
	void setBin(Bin* bin);
	Bin* getSolvedBin()
	{
		if (solved)
		{
			return bin;
		}
		return NULL;
	}
	std::vector<Box*>* getPlacedBoxes()
	{
		if (solved)
		{
			return &placedBoxes;
		}
		return NULL;
	}

protected:
	bool fitsIntoBin(Box* box);
	bool collidesWithOtherBoxes(Box* box);
	void setOptimalHeight(Box* box);
	bool solved;
	Bin* bin;
	int resultHeight;
	std::vector<Box*> unplacedBoxes;
	std::vector<Box*> placedBoxes;
};

#endif