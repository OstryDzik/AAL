/*
* Autor: Filip £êczycki
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
	int fitIntoSpace(Box* box, Space space); //funkcja podejmuje próbê dopasowania pude³ka do wolnego miejsca
    int fitIntoSpaceMaxSurface(Box* box, Space space); //funkcja podejmuje próbê dopasowania pude³ka do wolnego miejsca ( obróconego tak, by podstawa mia³a jak najwiêksz¹ powierzchniê)
	Node* insert(Box* box, Node* node); // funkcja próbuje umieœcic pude³ko na warstwie
	void clearNode(Node* node);
	void resetRoot();
	int solveLayer();
	Node root;
};


#endif 
