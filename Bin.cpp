/*
* Autor: Filip Łęczycki
*
* 3D Bin Packing Problem Solver
*/

#include <stdlib.h>
#include <algorithm>
#include "Bin.h"

bool compareBoxes(Box* a, Box* b)
{
	return (a->getVolume() > b->getVolume());
}

Bin::Bin(int sizeX, int sizeY)
{
	// warunki początkowe
	this->sizeX = sizeX;
	this->sizeZ = sizeY;
	this->boxCount = 0;
	this->unplacedBoxes.clear();
}

Bin::~Bin()
{
	this->reset();
}

void Bin::generate(int N, int minA, int maxA)
{
    this->reset();
    if (minA > maxA)
	{
		std::cout << "# Rozmiar minimalny nie może być większy od maksymalnego" << std::endl;
		return;
	}
	if (maxA > sizeX || maxA > sizeZ)
	{
		std::cout << "# Rozmiar maksymalny nie może być większy od granic obszaru" << std::endl;
		return;
	}
	this->boxCount = N;
	this->unplacedBoxes.reserve(N);
	std::cout << "# Generowanie..." << std::endl;
	int range = maxA - minA;
	if (range<=0)
	{
		std::cout << "# Podano zle wymiary" << std::endl;
		return;
	}
	for (int i = 0; i < N; i++)
	{
		Box* box = new Box(rand() % range + minA, rand() % range + minA, rand() % range + minA, i);
		addBox(box);
	}
	sortBoxes();
	std::cout << "# Wygenerowano..." << std::endl;
}

void Bin::clear(std::vector<Box*>* boxes)
{
	boxes->clear();
}

void Bin::reset()
{
	for (signed int i = 0; i < unplacedBoxes.size(); i++)
	{
		delete unplacedBoxes.at(i);
	}
	this->clear(&(this->unplacedBoxes));

}

std::string Bin::printUnsolvedBin()
{
	std::string bin = "Input bin size and boxes\n";
    bin += printSize();
	bin += ("##################################################\n");
	for (int i = 0; i < unplacedBoxes.size(); i++)
	{
		bin += unplacedBoxes.at(i)->printBox();
	}
	return bin;
}

std::string Bin::printSize()
{
    return ("Bin foot size: " + std::to_string(getSizeX()) + "," + std::to_string(getSizeZ()) + "\n");
}

