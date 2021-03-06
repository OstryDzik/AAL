/*
* Autor: Filip ��czycki
*
* 3D Bin Packing Problem Solver
*/

#include "ShelfSolver.h"

int ShelfSolver::solve()
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
    int furthestPoint = 0;
    int placedOnShelf = 0;
	unsigned int i = 0;
	for (unsigned int j = 0; j < unplacedBoxes.size(); j++)
	{
		setOptimalHeight(unplacedBoxes.at(j));
	}
    while (unplacedBoxes.size()!=0)
	{
		if (i>unplacedBoxes.size()-1) // odci�cie warstwy, powr�t do punktu 0,y,0
		{
            i = 0;
            if (placedOnShelf == 0) //je�eli nie zmiescilo si� wiecej na dan� warstw� zaczynamy now�
            {
                placingPos.x = 0;
                placingPos.z = 0;
                placingPos.y = yPos;
                furthestPoint = 0;
            }
            else // zaczynamy kolejn� p�k�
            {
                placedOnShelf = 0;
                if (isBinWider)
                {
                    placingPos.x = 0;
                    placingPos.z = furthestPoint;
                }
                else
                {
                    placingPos.x = furthestPoint;
                    placingPos.z = 0;
                }
            }
		}
		Box* current = new Box(this->unplacedBoxes.at(i));	
		if (this->fitsIntoPosition(placingPos, current)) //jezeli klocek zmiesci si� do koszyka
		{
			if (yPos < current->getPosY()+current->getY()) //jezeli klocek jest pierwszy w nowej warstwie zwi�kszamy aktualna wysokosc
			{
                yPos = current->getPosY() + current->getY();
			}

			this->placedBoxes.push_back(current);
			this->unplacedBoxes.erase(this->unplacedBoxes.begin() + i);

			if (isBinWider)
			{
				placingPos.x += current->getX();
                if (current->getZ() + current->getPosZ()>furthestPoint)
                {
                    furthestPoint = current->getZ() + current->getPosZ();
                }
			}
			else
			{
				placingPos.z += current->getZ();
                if (current->getX() + current->getPosX()>furthestPoint)
                {
                    furthestPoint = current->getX() + current->getPosX();
                }
			}
            placedOnShelf++; //udalo sie dodac klocek, zwiekszamy licznik
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


bool ShelfSolver::fitsIntoPosition(Position pos, Box* box)
{
	box->setPos(pos);
	if (!fitsIntoBin(box))
	{
		return false;
	}
	return true;
}



std::string ShelfSolver::printShortResult()
{
	std::string result;
	if (!solved)
	{
		result = "Not solved yet";
		return result;
	}
	result += "Bin solved with shelf algorithm: \n";
    result += "Elapsed time: " + std::to_string(elapsedTime) + "\n";
	result += "Bin height: " + std::to_string(bin->getSizeY()) +"\n";
	return result;
}