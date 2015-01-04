#ifndef TRIVIALSOLVER_H
#define TRIVIALSOLVER_H

#include <iostream>
#include <vector>
#include "Solver.h"

class TrivialSolver : public Solver
{
public:
	std::string printResult();
	std::string printShortResult();
	TrivialSolver(Bin* bin) : Solver(bin){};
	int solve();
private:
	bool fitsIntoPosition(Position pos, Box* box, int currentHeight);
};


#endif // TRIVIALSOLVER_H

