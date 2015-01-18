/*
* Autor: Filip ��czycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once
#include <vector>
#include "Bin.h"
#include "Solver.h"
#include "LayerSolver.h"
#include "NaiveSolver.h"
#include "ShelfSolver.h"
#include "FileManager.h"

class Experiment
{
public:    
    Experiment(int sampleCount, std::vector<int> sampleSize, int binSizeX, int binSizeZ, int boxMaxSize, int boxMinSize);
    void run();
    void printResult(std::string fileName = "");
    ~Experiment();
private:
    int sampleCount;
    std::vector<int> sampleSize;
    Bin* bin;
    int maxSize;
    int minSize;
    std::string result;
};

