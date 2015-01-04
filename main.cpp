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

#define LINE "---------------------------------------------\n"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include "Scena.h"
#include "Bin.h"
#include "TrivialSolver.h"
#include "LayerSolver.h"
#include "ThirdSolver.h"
#include "FileManager.h"
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
	std::cout << "# Podaj nazwę pliku" << std::endl << ": ";
	std::cin >> fileName;
	return FileManager::loadBinFromFile(fileName);
}

void solveBin(int argc, char** argv, Bin* bin)
{
	int alg;
	std::cout << "# Wybierz algorytm do rozwiązania problemu:" << std::endl;
	std::cout << "0 - Wszystkie poniższe" << std::endl;
	std::cout << "1 - Algorytm trywialny" << std::endl;
	std::cout << "2 - Algorytm warstwowy z naiwnym rozmieszczeniem pudelek" << std::endl;
	std::cout << "3 - Algorytm warstwowy z wykorzystaniem drzewa wolnej przestrzeni do optymalizacji rozmieszczenia" << std::endl << ": ";
	std::cin >> alg;
	Solver* trivialSolver = new TrivialSolver(bin);
	Solver* thirdSolver = new ThirdSolver(bin);
	Solver* layerSolver = new LayerSolver(bin);
	if (alg == 0)
	{
		trivialSolver->solve();
		std::cout << trivialSolver->printShortResult();	
		thirdSolver->solve();
		std::cout << thirdSolver->printShortResult();
		layerSolver->solve();
		std::cout << layerSolver->printShortResult();
	}
	else if (alg == 1)
	{
		trivialSolver->solve();
		std::cout << trivialSolver->printShortResult();
	}
	else if (alg == 2)
	{
		thirdSolver->solve();
		std::cout << thirdSolver->printShortResult();
	}
	else if (alg == 3)
	{
		layerSolver->solve();
		std::cout << layerSolver->printShortResult();
	}
	else
	{
		std::cout << "Zle polecenie" << std::endl;
		return;
	}

	Scena::start(argc, argv, bin, trivialSolver->getPlacedBoxes(), layerSolver->getPlacedBoxes(), thirdSolver->getPlacedBoxes());
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
	std::cout << "- p: wypisanie aktualnie wczytanych danych testowych" << std::endl;
	std::cout << "- s: rozwiazanie problemu z wczytanych danych wejsciowych" << std::endl;
	std::cout << "- q: wyjscie" << std::endl;
}

/**
 * Funkcja główna.
 */
int main(int argc, char** argv)
{
	srand(time(NULL));

	std::string command = "h";
	std::cout << LINE << "Filip Łęczycki - projekt z przedmiotu AAL\n" << LINE;
	Bin* bin = NULL;
	do
	{
		if (command == "h")
		{
			help();
		}
		else if (command == "r")
		{
			bin = generateData(argc, argv);
		}
		else if (command == "l")
		{
			bin = loadBin();
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
		std::getline(std::cin, command);
	} while (command != "q" && command != "exit" && command != "quit");

	std::cout << LINE << "Koniec programu, do zobaczenia!";

	return 0;
}
