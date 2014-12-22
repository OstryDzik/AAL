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
#include "Obszar.h"

/**
 * Renderuje obszar.
 */
void renderuj(int argc, char** argv)
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

	Obszar* obsz = new Obszar(obszarX, obszarY);
	obsz->generuj(ile, minA, maxA);
	obsz->algorithmTrivial();

	Scena::start(argc, argv, obsz);
	Scena::close();

	delete obsz;
}

/**
 * Wyświetla pomoc.
 */
void help()
{
	std::cout << "# dostepne polecenia: " << std::endl;
	std::cout << "- h: pomoc" << std::endl;
	std::cout << "- r: rendering" << std::endl;
	std::cout << "- q: wyjscie" << std::endl;
}

/**
 * Funkcja główna.
 */
int main(int argc, char** argv)
{
	srand(time(NULL));

	std::string command = "h";
	std::cout << LINE << "Marcin Jelenski - projekt z przedmiotu AAL\n" << LINE;

	do
	{
		if (command == "h")
		{
			help();
		}
		else if (command == "r")
		{
			renderuj(argc, argv);
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
