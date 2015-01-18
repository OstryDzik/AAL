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
    result += "ID|Size|ShelfAlg time|ShelfAlg Op Count|ShelfAlg H|LayerAlg time|LayerAlg Op Count|LayerAlg H|NaiveAlg time|NaiveAlg Op Count|NaiveAlg H\n";
    Solver* trivialSolver = new TrivialSolver(bin);
    Solver* thirdSolver = new ThirdSolver(bin);
    Solver* layerSolver = new LayerSolver(bin);
    double timeTrivial, timeThird, timeLayer;
	int opCountTrivial, opCountThird, opCountLayer;
    for (int i = 0; i < sampleCount; i++)
    {
        bin->generate(this->sampleSize.at(i), this->minSize, this->maxSize);
        trivialSolver->setBin(bin); //shelf
        thirdSolver->setBin(bin); //naive
        layerSolver->setBin(bin); //layer
        timeTrivial = trivialSolver->solveWithTimeMeasure()*1000;
        timeThird = thirdSolver->solveWithTimeMeasure()*1000;
        timeLayer = layerSolver->solveWithTimeMeasure()*1000;
		opCountLayer = layerSolver->getComparisonCount();
		opCountThird = thirdSolver->getComparisonCount();
		opCountTrivial = trivialSolver->getComparisonCount();
        result += std::to_string(i + 1) + "|" + std::to_string(this->sampleSize.at(i)) + "|"
			+ std::to_string(timeTrivial) + "|" + std::to_string(opCountTrivial) + "|" + std::to_string(trivialSolver->getResultHeight()) + "|"
			+ std::to_string(timeLayer) + "|" + std::to_string(opCountLayer) + std::to_string(layerSolver->getResultHeight()) + "|"
			+ std::to_string(timeThird) + "|" + std::to_string(opCountThird) + std::to_string(thirdSolver->getResultHeight()) + "|" + "\n";
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