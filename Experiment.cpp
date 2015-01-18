/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#include "Experiment.h"

Experiment::~Experiment()
{
}

Experiment::Experiment(int sampleCount, std::vector<int> sampleSize, int binSizeX, int binSizeZ, int boxMaxSize, int boxMinSize)
{
    this->sampleCount = sampleCount;
    this->sampleSize = sampleSize;
    bin = new Bin(binSizeX, binSizeZ);
    this->minSize = boxMinSize;
    this->maxSize = boxMaxSize;
    result = "";
}

void Experiment::run()
{
	std::sort(sampleSize.begin(), sampleSize.end());
	if (sampleSize.size()%2==1)
	{
		int median =sampleSize.at((sampleSize.size() - 1) / 2 + 1); //srodkowa wartosc posortowanego wektora
	}
	else
	{
		int median = sampleSize.at(sampleSize.size() / 2);
	}

    std::string result;
    result += bin->printSize();
    result += "Samples count: " + std::to_string(sampleCount) + "\n";
    result += "ID|Size|ShelfAlg time|ShelfAlg H|LayerAlg time|LayerAlg H|NaiveAlg time|NaiveAlg H\n";
    Solver* shelfSolver = new ShelfSolver(bin);
    Solver* naiveSolver = new NaiveSolver(bin);
    Solver* layerSolver = new LayerSolver(bin);
    double timeShelf, timeNaive, timeLayer;
	int opCountShelf, opCountNaive, opCountLayer;
    for (int i = 0; i < sampleCount; i++)
    {
        bin->generate(this->sampleSize.at(i), this->minSize, this->maxSize);
        shelfSolver->setBin(bin); //shelf
        naiveSolver->setBin(bin); //naive
        layerSolver->setBin(bin); //layer
        timeShelf = shelfSolver->solveWithTimeMeasure()*1000;
        timeNaive = naiveSolver->solveWithTimeMeasure()*1000;
        timeLayer = layerSolver->solveWithTimeMeasure()*1000;
		opCountLayer = layerSolver->getComparisonCount();
		opCountNaive = naiveSolver->getComparisonCount();
		opCountShelf = shelfSolver->getComparisonCount();
        result += std::to_string(i + 1) + "|" + std::to_string(this->sampleSize.at(i)) + "|"
			+ std::to_string(timeShelf) + "|" + std::to_string(shelfSolver->getResultHeight()) + "|"
			+ std::to_string(timeLayer) + "|" + std::to_string(layerSolver->getResultHeight()) + "|"
			+ std::to_string(timeNaive) + "|" + std::to_string(naiveSolver->getResultHeight()) + "|" + "\n";
    }
    this->result = result;
}

void Experiment::printResult(std::string fileName)
{
    if (fileName == "")
    {
        std::cout << result;
    }
    else
    {
        if (!FileManager::saveToFile(result, fileName))
        {
            std::cout << "Nie udalo sie zapisac";
        }
    }
}