#ifndef THIRDSOLVER_H
#define THIRDSOLVER_H

#include "Solver.h"

class ThirdSolver : public Solver
{
public:
	ThirdSolver(Bin* bin);
	~ThirdSolver();
	int solve();
	std::string printResult();
	std::string printShortResult();
};

#endif

