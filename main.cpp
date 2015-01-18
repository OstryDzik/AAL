/////////////////////////////////////////////////////////////////////////////////
//
//
//    Dany jest zbiór prostopadłościanów {a1, … , an} oraz obszar
//    prostopadłościenny o zadanych dwóch bokach nie mniejszych od
//    największego z boków prostopadłościanów w zbiorze. Należy wyznaczyć,
//    stosując różne metody heurystyczne, a także przeszukiwanie
//    systematyczne, najmniejszą dlugość trzeciego boku obszaru pozwalającą na
//    rozmieszczenie ortogonalne bez kolizji zbioru w obszarze. Porównać czas
//    obliczeń i wyniki różnych metod.
//
//    ---------------------------------------------------------------------------
//
//    Wymagania nie odbiegają od predstawionych na zajęciach wprowadzających,
//    z tą uwagą, że chciałbym, żeby porównali Państwo kilka (orientacyjne 3)
//    możliwie różnych algorytmów.
//
//    W razie pytań proszę kontaktować się ze mną drogą mailową. Na
//    konsultacje zapraszam we wtorki, w godz. 14:15-16:15, do pokoju 309, ale
//    najprawdopodobniej dopiero od pierwszego lub drugiego tygodnia listopada.
//
//
///////////////////////////////////////////////////////////////////////////////////

/*
* Autor: Filip Łęczycki
*
* 3D Bin Packing Problem Solver
*/

#define LINE "---------------------------------------------\n"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include "Scena.h"
#include "Bin.h"
#include "ShelfSolver.h"
#include "LayerSolver.h"
#include "NaiveSolver.h"
#include "FileManager.h"
#include "Experiment.h"

Experiment* loadExperiment()
{
	std::string fileName;
	std::cout << "# Podaj nazwe pliku" << std::endl << ": ";
	std::cin >> fileName;
	return FileManager::loadExperimentFromFile(fileName);
}

void runExperimentFromFile()
{
	Experiment* exp = loadExperiment();
	if (exp==NULL)
	{
		std::cout << "Nie udalo sie wczytac danych\n";
		return;
	}
	exp->run();
	std::string saveFile;
	std::string fileName;
	std::cout << "# Zapisac wynik do pliku? Y/N" << std::endl << ": ";
	std::cin >> saveFile;
	if (saveFile == "Y" || saveFile == "y")
	{
		std::cout << "# Podaj nazwe pliku" << std::endl << ": ";
		std::cin >> fileName;
		exp->printResult(fileName);
	}
	else
	{
		exp->printResult();
	}
}

void runExperimentManual()
{
    std::vector<int> resultsSize;
    int count, obszarX, obszarZ, minA, maxA, size;
    std::cout << "# Prosze podac wymiary obszaru, liczbe oraz rozmiar kazdej z probek" << std::endl << ": ";
    std::cout << "# Rozmiar obszaru (x): " << std::endl << ": ";
    std::cin >> obszarX;
    std::cout << "# Rozmiar obszaru (z): " << std::endl << ": ";
    std::cin >> obszarZ;
    std::cout << "# Min. krawedz: " << std::endl << ": ";
    std::cin >> minA;
    std::cout << "# Maks. krawedz: " << std::endl << ": ";
    std::cin >> maxA;
    std::cout << "# Ile probek wygenerowac?" << std::endl << ": ";
    std::cin >> count;
    for (int i = 0; i < count; i++)
    {
        std::cout << "# Podaj rozmiar probki " + std::to_string(i+1) + " z "+ std::to_string(count) << std::endl << ": ";
        std::cin >> size;
        while (size<=0)
        {
            std::cout << "# Podaj rozmiar wiekszy od 0" << std::endl << ": ";
            std::cin >> size;
        }
        resultsSize.push_back(size);
    }
    Experiment* exp = new Experiment(count, resultsSize, obszarX, obszarZ, maxA, minA);
    exp->run();
    std::string saveFile;
    std::string fileName;
    std::cout << "# Zapisac wynik do pliku? Y/N" << std::endl << ": ";
    std::cin >> saveFile;
    if (saveFile == "Y" || saveFile == "y")
    {
        std::cout << "# Podaj nazwe pliku" << std::endl << ": ";
        std::cin >> fileName;
        exp->printResult(fileName);
    }
    else
    {
        exp->printResult();
    }
}
/**
 * Renderuje obszar.
 */
Bin* generateData(int argc, char** argv)
{
	int ile, obszarX, obszarY, minA, maxA;
	std::cout << "# Ile figur wygenerowac?" << std::endl << ": ";
	std::cin >> ile;
	std::cout << "# Rozmiar obszaru (x): " << std::endl << ": ";
	std::cin >> obszarX;
	std::cout << "# Rozmiar obszaru (z): " << std::endl << ": ";
	std::cin >> obszarY;
	std::cout << "# Min. krawedz: " << std::endl << ": ";
	std::cin >> minA;
	std::cout << "# Maks. krawedz: " << std::endl << ": ";
	std::cin >> maxA;

	Bin* obsz = new Bin(obszarX, obszarY);
	obsz->generate(ile, minA, maxA);
	return obsz;
}

Bin* loadBin()
{
	std::string fileName;
	std::cout << "# Podaj nazwe pliku" << std::endl << ": ";
	std::cin >> fileName;
	return FileManager::loadBinFromFile(fileName);
}



void solveBin(int argc, char** argv, Bin* bin)
{
	int alg;
	std::cout << "# Wyniki zostaną przedstawione w konsoli, przełaczanie wizualizacji odbywa sie klawiszami odpowiednio 1,2,3:" << std::endl;
	std::cout << "# Wybierz algorytm do rozwiazania problemu:" << std::endl;
	std::cout << "0 - Wszystkie ponizsze" << std::endl;
	std::cout << "1 - Algorytm naiwny" << std::endl;
	std::cout << "2 - Algorytm warstwowy z 'polkowym' rozmieszczeniem pudelek" << std::endl;
	std::cout << "3 - Algorytm warstwowy z wykorzystaniem drzewa wolnej przestrzeni" << std::endl << ": ";
	std::cin >> alg;
	Solver* trivialSolver = new ShelfSolver(bin);
	Solver* thirdSolver = new NaiveSolver(bin);
	Solver* layerSolver = new LayerSolver(bin);
	if (alg == 0)
	{
		trivialSolver->solveWithTimeMeasure();
		std::cout << trivialSolver->printShortResult();	
		thirdSolver->solveWithTimeMeasure();
		std::cout << thirdSolver->printShortResult();
		layerSolver->solveWithTimeMeasure();
		std::cout << layerSolver->printShortResult();
	}
	else if (alg == 1)
	{
		trivialSolver->solveWithTimeMeasure();
		std::cout << trivialSolver->printShortResult();
	}
	else if (alg == 2)
	{
		thirdSolver->solveWithTimeMeasure();
		std::cout << thirdSolver->printShortResult();
	}
	else if (alg == 3)
	{
		layerSolver->solveWithTimeMeasure();
		std::cout << layerSolver->printShortResult();
	}
	else
	{
		std::cout << "Zle polecenie" << std::endl;
		return;
	}

    Scena::start(argc, argv, bin, trivialSolver->getPlacedBoxes(), thirdSolver->getPlacedBoxes(), layerSolver->getPlacedBoxes());
	Scena::close();
}

/**
 * Wyświetla pomoc.
 */
void help()
{
	std::cout << "# dostepne polecenia: " << std::endl;
	std::cout << "- h: pomoc" << std::endl;
	std::cout << "- r: generowanie danych testowych" << std::endl;
	std::cout << "- l: wczytanie danych z pliku" << std::endl;
    std::cout << "- em: przeprowadzenie eksperymentu - reczne wprwadzanie danych" << std::endl;
	std::cout << "- ef: przeprowadzenie eksperymentu - dane z pliku" << std::endl;
	std::cout << "- p: wypisanie aktualnie wczytanych danych testowych" << std::endl;
	std::cout << "- s: rozwiazanie problemu z wczytanych danych testowych" << std::endl;
	std::cout << "- q: wyjscie" << std::endl;
}

/**
 * Funkcja główna.
 */
int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	std::string command = "h";
	std::cout << LINE << "Filip Leczycki - projekt z przedmiotu AAL\n" << LINE;
	Bin* bin = NULL;
	do
	{		
        if (command == "h")
		{
			
		}
		else if (command == "r")
		{
			bin = generateData(argc, argv);
		}
        else if (command == "em")
        {
            runExperimentManual();
        }
		else if (command == "ef")
		{
			runExperimentFromFile();
		}
		else if (command == "l")
		{
			bin = loadBin();
            if (bin==NULL)
            {
                std::cout << "Zadne dane nie zostaly wczytane" << std::endl;
            }
		}
		else if (command == "s")
		{
			if (bin != NULL)
			{
				solveBin(argc, argv, bin);
			}
			else
			{
				std::cout << "Zadne dane nie zostaly wczytane" << std::endl;
			}
		}
		else if (command == "p")
		{
			if (bin != NULL)
			{
				std::cout << bin->printUnsolvedBin();
			}
			else
			{
				std::cout << "Zadne dane nie zostaly wczytane" << std::endl;
			}
		}
		else
		{
			std::cout << "# nieznane polecenie" << std::endl;
		}
		std::cout << std::endl << LINE << ": ";
        help();
        std::cin >> command;
	} while (command != "q" && command != "exit" && command != "quit");

	std::cout << LINE << "Koniec programu, do zobaczenia!";

	return 0;
}
