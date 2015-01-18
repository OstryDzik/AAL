/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include "Bin.h"

class Solver
{
public:
    //funkcje wirtualne, implementacja ró¿ni siê w zale¿noœci od klasy solvera
    virtual int solve() = 0;
    virtual std::string printShortResult() = 0;

	Solver(Bin* bin);
	~Solver();

    double solveWithTimeMeasure();
    std::string printResult();
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
    int getResultHeight()
    {
        if (solved)
        {
            return resultHeight;
        }
        else return -1;
    }
	int getComparisonCount()
	{
		if (solved)
		{
			return comparisonCount;
		}
		else return -1;
	}
protected:
	bool fitsIntoBin(Box* box);
	void setOptimalHeight(Box* box);
	bool solved;
	Bin* bin;
	int resultHeight;
	int comparisonCount;
    double elapsedTime;
	std::vector<Box*> unplacedBoxes;
	std::vector<Box*> placedBoxes;
};

#endif