/*
 * Autor: Filip £êczycki
 *
 * 3D Bin Packing Problem Solver
 */

#ifndef BIN_H
#define BIN_H
#pragma once
#include <iostream>
#include <vector>
#include "Box.h"
#include <stdlib.h>
#include <algorithm>

bool compareBoxes(Box* a, Box* b);


class Bin
{
public:
	Bin(int sizeX, int sizeY);
	virtual ~Bin();

	void generate(int N, int minA, int maxA);
	void clear(std::vector<Box*>* boxes);
	void clearPlaced();
	void reset();

	void setSizeY(int y)
	{
		this->sizeY = y;
	}

	int getSizeX()
	{
		return sizeX;
	}

	int getSizeZ()
	{
		return sizeZ;
	}

	int getSizeY()
	{
		return sizeY;
	}

	int getBoxCount()
	{
		return boxCount;
	}

	std::vector<Box*> getUnplacedBoxes()
	{
		return unplacedBoxes;
	}

	void addBox(Box* box)
	{
		this->unplacedBoxes.push_back(box);
		this->boxCount = this->unplacedBoxes.size();
	}

	void sortBoxes()
	{
		std::sort(unplacedBoxes.begin(), unplacedBoxes.end(), compareBoxes);
	}

	std::string printUnsolvedBin();
    std::string printSize();
private:
	int sizeX, sizeZ, sizeY; // wymiary obszaru
	int boxCount;
	std::vector<Box*> unplacedBoxes;
};

#endif /* BIN_H */
