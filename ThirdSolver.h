/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#ifndef THIRDSOLVER_H
#define THIRDSOLVER_H

#include "Solver.h"

class ThirdSolver : public Solver
{
public:
	ThirdSolver(Bin* bin);
	~ThirdSolver();
	int solve();
	std::string printShortResult();
};

#endif

