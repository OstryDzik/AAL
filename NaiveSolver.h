/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once

#include "Solver.h"

class NaiveSolver : public Solver
{
public:
	NaiveSolver(Bin* bin);
	~NaiveSolver();
	int solve();
	std::string printShortResult();
};


