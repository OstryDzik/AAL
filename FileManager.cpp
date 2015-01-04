#include "FileManager.h"


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

Bin* FileManager::loadBinFromFile(std::string filename)
{
	std::ifstream readFile;
	readFile.open(filename);
	Bin* bin = NULL;
	if (readFile.is_open())
	{
		std::string line;
		if (std::getline(readFile, line))
		{
			std::stringstream stringLine(line);
			std::string tmp, tmpX, tmpY;
			if (std::getline(stringLine, tmp, ':') &&
				std::getline(stringLine, tmpX, ',') && 
				std::getline(stringLine, tmpY))
			{
				if (tmp != "bin")
				{
					return NULL;
				}
				bin = new Bin(std::stoi(tmpX), std::stoi(tmpY));
			}
		}
	}
	if (bin!=NULL)
	{
		std::string boxLine;
		int ID=0;
		while (std::getline(readFile, boxLine))
		{
			std::stringstream stringLine(boxLine);
			std::string tmp, tmpX, tmpY, tmpZ;
			if (std::getline(stringLine, tmp, ':') &&
				std::getline(stringLine, tmpX, ',') &&
				std::getline(stringLine, tmpY, ',') && 
				std::getline(stringLine, tmpZ))
			{
				if (tmp == "box")
				{
					Box* box = new Box(std::stoi(tmpX), std::stoi(tmpY), std::stoi(tmpZ), ID);
					bin->addBox(box);
					ID++;
				}
			}
		}
	}
	return bin;
}