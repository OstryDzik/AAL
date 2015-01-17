/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#include "LayerSolver.h"

LayerSolver::LayerSolver(Bin* bin) : Solver(bin)
{
	Point2D p1 = { 0, 0 };
	int x = bin->getSizeX();
	int y = bin->getSizeZ();
	Point2D p2 = { x, 0 };
	Point2D p3 = { 0, y };
	Point2D p4 = { x,y };

	root = { { NULL, NULL }, Space(p1, p2, p3, p4), false };
	resultHeight = 0;
}


int LayerSolver::fitIntoSpace(Box* box, Space space)
{
	if (box->getMinSurface() > space.getSurface())
	{
		return -1;
	}
	int bestRot = ROTATION_0;
	int surfaceLeft = -1;
	for (int rot = ROTATION_0; rot <= ROTATION_5; rot++)
	{
		box->setRotation(Rotation(rot));
		if (box->getSurface()<=space.getSurface() && box->getX() <= space.getWidth() && box->getZ() <= space.getLength())
		{
			if (surfaceLeft == -1 || surfaceLeft>space.getSurface() - box->getSurface())
			{
				surfaceLeft = space.getSurface() - box->getSurface();
				bestRot = rot;
			}
		}
	}
	box->setRotation((Rotation)bestRot);
	return surfaceLeft;
}

int LayerSolver::fitIntoSpaceMaxSurface(Box* box, Space space)
{
    if (box->getMinSurface() > space.getSurface())
    {
        return -1;
    }
    int bestRot = ROTATION_0;
    int surfaceLeft = -1;
    int boxSurface = 0;
    for (int rot = ROTATION_0; rot <= ROTATION_5; rot++)
    {
        box->setRotation(Rotation(rot));
        if (box->getSurface() > boxSurface)
        {
            boxSurface = box->getSurface();
            bestRot = rot;       
        }
    }
    box->setRotation((Rotation)bestRot);
    if (box->getSurface() <= space.getSurface() && box->getX() <= space.getWidth() && box->getZ() <= space.getLength())
    {
        surfaceLeft = space.getSurface() - box->getSurface();
    }
    return surfaceLeft;
}

Node* LayerSolver::insert(Box* box, Node* node)
{
	if (node->child[0] != NULL && node->child[1] != NULL)
	{
		Node* newNode = insert(box, node->child[0]);
		if (newNode != NULL)
		{
			return newNode;
		}
		return insert(box, node->child[1]);
	}
	else
	{
		if (node->occupied)
		{
			return NULL;
		}
		//int surfaceLeft = fitIntoSpace(box, node->space);
        int surfaceLeft = fitIntoSpaceMaxSurface(box, node->space);
		if (surfaceLeft==-1)
		{
			return NULL;
		}
		if (surfaceLeft == 0)
		{
			return node;
		}

		node->child[0] = new Node;
		node->child[0]->occupied = false;
		node->child[0]->child[0] = NULL;
		node->child[0]->child[1] = NULL;
		node->child[1] = new Node;
		node->child[1]->occupied = false;
		node->child[1]->child[0] = NULL;
		node->child[1]->child[1] = NULL;

		int dw = node->space.getWidth() - box->getX();
		int dh = node->space.getLength() - box->getZ();

		if (dw>dh) //pionowy podzial miejsca
		{
			node->child[0]->space = Space(node->space.getTopLeft(), box->getX(), node->space.getLength());
			node->child[1]->space = Space({ node->space.getTopLeft().x + box->getX(), node->space.getTopLeft().y }, node->space.getWidth() - box->getX(), node->space.getLength());
		}
		else // poziomy podzial miejsca
		{
			node->child[0]->space = Space(node->space.getTopLeft(), node->space.getWidth(), box->getZ());
			node->child[1]->space = Space({ node->space.getTopLeft().x, node->space.getTopLeft().y + box->getZ() }, node->space.getWidth(), node->space.getLength()-box->getZ());
		}
		return insert(box, node->child[0]);
	}
}

void LayerSolver::clearNode(Node* node)
{
	if (node== NULL)
	{
		return;
	}
	clearNode(node->child[0]);
	clearNode(node->child[1]);
	delete node;
}

void LayerSolver::resetRoot()
{
	clearNode(root.child[0]);
	clearNode(root.child[1]);
	Point2D p1 = { 0, 0 };
	int x = bin->getSizeX();
	int y = bin->getSizeZ();
	Point2D p2 = { x, 0 };
	Point2D p3 = { 0, y };
	Point2D p4 = { x, y };
	root = { { NULL, NULL }, Space(p1, p2, p3, p4), false };
}

int LayerSolver::solveLayer()
{
	resetRoot(); // czysci drzewo, zaczynamy od pustej warstwy
	int topHeight = 0;
	for (int i = 0; i < unplacedBoxes.size(); i++)
	{
		Box* currentBox = new Box(unplacedBoxes.at(i));
		Node* currentNode = (insert(currentBox, &root));
		if (currentNode!=NULL)
		{
			currentBox->setPos(currentNode->space.getTopLeft().x, resultHeight, currentNode->space.getTopLeft().y);
			placedBoxes.push_back(currentBox);
			currentNode->occupied = true;
			unplacedBoxes.erase(this->unplacedBoxes.begin() + i);
			i = -1;
			if (currentBox->getY()>topHeight)
			{
				topHeight = currentBox->getY();
			}
		}
	}

	return topHeight;
}

int LayerSolver::solve()
{
	reset();
	if (bin == NULL || unplacedBoxes.empty())
	{
		return -1;
	}
	while (unplacedBoxes.size()!=0)
	{
		resultHeight += solveLayer();
	}
	bin->setSizeY(resultHeight);
	solved = true;
	return resultHeight;
}


std::string LayerSolver::printShortResult()
{
	std::string result;
	if (!solved)
	{
		result = "Not solved yet";
		return result;
	}
	result += "Bin solved with Layer algorithm: \n";
    result += "Elapsed time: " + std::to_string(elapsedTime) + "\n";
	result += "Bin height: " + std::to_string(resultHeight) +"\n";
	return result;
}

LayerSolver::~LayerSolver()
{
	resetRoot();
}