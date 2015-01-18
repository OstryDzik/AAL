/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/


#include "NaiveSolver.h"

NaiveSolver::NaiveSolver(Bin* bin) : Solver(bin)
{

}


int NaiveSolver::solve()
{
	reset();
	if (bin == NULL || unplacedBoxes.empty())
	{
		return -1;
	}
	while (unplacedBoxes.size()!=0)
	{
		Box* currentBox = new Box(unplacedBoxes.at(0));
		setOptimalHeight(currentBox);
		currentBox->setPos( 0, resultHeight, 0);
		placedBoxes.push_back(currentBox);
		resultHeight += currentBox->getY();
		unplacedBoxes.erase(unplacedBoxes.begin());
	}
	bin->setSizeY(resultHeight);
	solved = true;
	return resultHeight;
}



std::string NaiveSolver::printShortResult()
{
	std::string result;
	if (!solved)
	{
		result = "Not solved yet";
		return result;
	}
	result += "Bin solved with Naive algorithm: \n";
    result += "Elapsed time: " + std::to_string(elapsedTime) + "\n";
	result += "Bin height: " + std::to_string(resultHeight) + "\n";
	return result;
}

