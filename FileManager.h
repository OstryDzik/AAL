/*
* Autor: Filip Łęczycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once
#include <string>
#include "Bin.h"
#include  <istream>
#include <fstream>
#include <sstream>


class FileManager
{
public:
	FileManager();
	~FileManager();

	//funkcja wczytuje dane z pliku
	//format pliku jest następujący:
	//bin:x,y
	//box:x,y,z
	//box:x,y,z
	static Bin* loadBinFromFile(std::string fileName);
	static bool saveToFile(std::string content, std::string fileName);
};

