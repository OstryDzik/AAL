/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once
#include <string>
#include "Bin.h"
#include  <istream>
#include <fstream>
#include <sstream>
#include "Experiment.h"


class FileManager
{
public:
	FileManager();
	~FileManager();

	static Bin* loadBinFromFile(std::string fileName);
	static bool saveToFile(std::string content, std::string fileName);
	static Experiment* loadExperimentFromFile(std::string fileName);
};

