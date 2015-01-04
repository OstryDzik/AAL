#include "TrivialSolver.h"

int TrivialSolver::solve()
{
	reset();
	if (bin == NULL || unplacedBoxes.empty())
	{
		return -1;
	}
	int yPos = 0;
	bool isBinWider = bin->getSizeX() > bin->getSizeZ();
	Position placingPos;
	placingPos.x = 0;
	placingPos.y = 0;
	placingPos.z = 0;
	int i = 0;
	bool newLayer = true;
	while (unplacedBoxes.size()!=0)
	{
		if (i>unplacedBoxes.size()-1) // odciêcie warstwy, powrót do punktu 0,y,0
		{
			i = 0;
			placingPos.x = 0;
			placingPos.z = 0;
			placingPos.y = yPos;
			newLayer = true;
		}
		Box* current = new Box(this->unplacedBoxes.at(i));	
		if (this->fitsIntoPosition(placingPos, current, yPos))
		{
			if (newLayer) //jezeli klocek jest pierwszy w nowej warstwie zwiêkszamy limit wysokosci
			{
				yPos+= current->getY();
				newLayer = false;
			}
			this->placedBoxes.push_back(current);
			this->unplacedBoxes.erase(this->unplacedBoxes.begin() + i);
			if (isBinWider)
			{
				placingPos.x += current->getX();
			}
			else
			{
				placingPos.z += current->getZ();
			}
			i = 0;
		}
		else
		{
			i++;
			delete current;
		}		
	}
	bin->setSizeY(yPos);
	solved = true;
	resultHeight = yPos;
	return resultHeight;
	
}


bool TrivialSolver::fitsIntoPosition(Position pos, Box* box, int currentHeight)
{
	box->setPos(pos);
	setOptimalHeight(box);
	if (!fitsIntoBin(box) || (box->getY()>currentHeight&& pos.x != 0 && pos.z != 0))
	{
		return false;
	}
	return true;
}

std::string TrivialSolver::printResult()
{
	std::string result;
	if (!solved)
	{
		result = "Not solved yet";
		return result;
	}
	result += "Bin solved with trivial algorithm: \n";
	result += printSolvedBoxes();
	return result;
}

std::string TrivialSolver::printShortResult()
{
	std::string result;
	if (!solved)
	{
		result = "Not solved yet";
		return result;
	}
	result += "Bin solved with trivial algorithm: \n";
	result += "Bin height: " + std::to_string(bin->getSizeY()) +"\n";
	return result;
}