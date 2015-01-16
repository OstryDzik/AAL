/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#include "Solver.h"
#include <chrono>
#include <ctime>

Solver::Solver(Bin* bin)
{
	this->bin = bin;
	this->unplacedBoxes = bin->getUnplacedBoxes();
	solved = false;
    elapsedTime = 0;
}

Solver::~Solver()
{
	for (int i = 0; i < placedBoxes.size(); i++)
	{
		delete placedBoxes.at(i);
	}
	unplacedBoxes.clear();
	placedBoxes.clear();
	bin = NULL;
}

bool Solver::fitsIntoBin(Box* box)
{
	if (box->getPosX() + box->getX() <= bin->getSizeX() && box->getPosZ() + box->getZ() <= bin->getSizeZ())
		return true;
	return false;
}

void Solver::setOptimalHeight(Box* box)
{
	int optimal = ROTATION_0;
	int optimalY = box->getY();
	for (int rot = ROTATION_1; rot <= ROTATION_5; rot++)
	{
		box->setRotation(Rotation(rot));
		int tempY = box->getY();
		if (tempY < optimalY && fitsIntoBin(box))
		{
			optimalY = tempY;
			optimal = rot;
		}
	}
	box->setRotation(Rotation(optimal));
}

std::string Solver::printSolvedBoxes()
{
	std::string result = "Solved bin box arrangement\n";
	result += ("Bin foot size: " + std::to_string(bin->getSizeX()) + "," + std::to_string(bin->getSizeZ()) + "\n");
	result += ("Bin height: " + std::to_string(this->resultHeight) + "\n");
	result += ("##################################################\n");
	for (int i = 0; i < this->placedBoxes.size(); i++)
	{
		result += placedBoxes.at(i)->printBox();
	}
	return result;
}

void Solver::reset()
{
	for (int i = 0; i < placedBoxes.size(); i++)
	{
		delete placedBoxes.at(i);
	}
	placedBoxes.clear();
	resultHeight = 0;
	unplacedBoxes = bin->getUnplacedBoxes();
}

void Solver::setBin(Bin* bin)
{
	this->bin = bin;
	reset();
}

double Solver::solveWithTimeMeasure()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    solve();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;
    this->elapsedTime = elapsedSeconds.count();
    return this->elapsedTime;
}

std::string Solver::printResult()
{
    std::string result;
    if (!solved)
    {
        result = "Not solved yet";
        return result;
    }
    result += printShortResult();
    result += printSolvedBoxes();
    return result;
}