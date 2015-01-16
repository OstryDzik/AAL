/*
* Autor: Filip ��czycki
*
* 3D Bin Packing Problem Solver
*/

#ifndef LAYERSOLVER_H
#define LAYERSOLVER_H

#include <iostream>
#include <vector>
#include "Solver.h"
#include "Space.h"



struct Node
{
	Node* child[2];
	Space space;
	bool occupied;
};


class LayerSolver : public Solver
{
public:
	~LayerSolver();
	LayerSolver(Bin* bin);
	int solve();
	std::string printShortResult();
private:
	int fitIntoSpace(Box* box, Space space); //funkcja podejmuje pr�b� dopasowania pude�ka do wolnego miejsca
    int fitIntoSpaceMaxSurface(Box* box, Space space); //funkcja podejmuje pr�b� dopasowania pude�ka do wolnego miejsca ( obr�conego tak, by podstawa mia�a jak najwi�ksz� powierzchni�)
	Node* insert(Box* box, Node* node); // funkcja pr�buje umie�cic pude�ko na warstwie
	void clearNode(Node* node);
	void resetRoot();
	int solveLayer();
	Node root;
};


#endif 
