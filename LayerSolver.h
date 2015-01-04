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
	std::string printResult();
	std::string printShortResult();
private:
	int fitIntoSpace(Box* box, Space space);
	Node* insert(Box* box, Node* node);
	void clearNode(Node* node);
	void resetRoot();
	int solveLayer();
	Node root;
};


#endif // TRIVIALSOLVER_H

