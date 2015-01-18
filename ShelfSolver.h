/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once

#include <iostream>
#include <vector>
#include "Solver.h"

class ShelfSolver : public Solver
{
public:
	std::string printShortResult();
	ShelfSolver(Bin* bin) : Solver(bin){};
	int solve();
private:
	bool fitsIntoPosition(Position pos, Box* box);
};


