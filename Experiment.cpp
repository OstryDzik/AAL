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
    std::string result;
    result += bin->printSize();
    result += "Samples count: " + std::to_string(sampleCount) + "\n";
    result += "ID | Size | TrivialAlg time | TrivialAlg size | LayerAlg time | LayerAlg size | NaiveAlg time | NaiveAlg size\n";
    Solver* trivialSolver = new TrivialSolver(bin);
    Solver* thirdSolver = new ThirdSolver(bin);
    Solver* layerSolver = new LayerSolver(bin);
    double time1, time2, time3;
    for (int i = 0; i < sampleCount; i++)
    {
        bin->generate(this->sampleSize.at(i), this->minSize, this->maxSize);
        trivialSolver->setBin(bin);
        thirdSolver->setBin(bin);
        layerSolver->setBin(bin);
        time1 = trivialSolver->solveWithTimeMeasure();
        time2 = thirdSolver->solveWithTimeMeasure();
        time3 = layerSolver->solveWithTimeMeasure();
        result += std::to_string(i + 1) + "|" + std::to_string(this->sampleSize.at(i)) + "|"
            + std::to_string(time1) + "|" + std::to_string(trivialSolver->getResultHeight()) + "|"
            + std::to_string(time3) + "|" + std::to_string(layerSolver->getResultHeight()) + "|"
            + std::to_string(time2) + "|" + std::to_string(thirdSolver->getResultHeight()) + "|" + "\n";
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