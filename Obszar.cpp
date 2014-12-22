/*
 * Obszar.cpp
 *
 *  Created on: 23 lis 2014
 *      Author: marcin
 */

#include <stdlib.h>
#include "Obszar.h"

Obszar::Obszar(int rozmiarX, int rozmiarY)
{
	// warunki początkowe
	this->rozmiarX = rozmiarX;
	this->rozmiarZ = rozmiarY;
	this->liczbaFigur = 0;
	this->figury.clear();
}

Obszar::~Obszar()
{
	this->wyczysc();
}

void Obszar::generuj(int N, int minA, int maxA)
{
	if (minA > maxA)
	{
		std::cout << "# Rozmiar minimalny nie może być większy od maksymalnego" << std::endl;
		return;
	}
	if (maxA > rozmiarX || maxA > rozmiarZ)
	{
		std::cout << "# Rozmiar maksymalny nie może być większy od granic obszaru" << std::endl;
		return;
	}
	this->liczbaFigur = N;
	this->figury.reserve(N);
	std::cout << "# Generowanie..." << std::endl;
	int range = maxA - minA;
	for (int i = 0; i < N; i++)
	{
		Figura* nowa = new Figura(rand() % range + minA, rand() % range + minA, rand() % range + minA);
		nowa->setPos(0, 0, 0);
		this->figury.push_back(nowa);
	}
	std::cout << "# Wygenerowano..." << std::endl;
}

void Obszar::wyczysc()
{
	if (this->liczbaFigur > 0)
	{
		for (int i = 0; i < this->liczbaFigur; i++)
		{
			delete this->figury[i];
		}
		this->figury.clear();
	}
	this->liczbaFigur = 0;
}

/**
 * Znajduje optymalną rotację dla figury
 */
void Obszar::setOptimalHeight(Figura* figura)
{
	int optimal = ROTATION_0;
	int optimalY = figura->getY();
	for (int rot = ROTATION_1; rot <= ROTATION_5; rot++)
	{
		figura->setRotation(Rotation(rot));
		int tempY = figura->getY();
		if (tempY < optimalY)
		{
			optimalY = tempY;
			optimal = rot;
		}
	}
	figura->setRotation(Rotation(optimal));
}

/**
 * Algorytm "trywialny".
 * Zwraca uzyskaną wysokość.
 */
int Obszar::algorithmTrivial()
{
	int yPos = 0;
	for (int i = 0; i < liczbaFigur; i++)
	{
		Figura* current = this->figury.at(i);
		this->setOptimalHeight(current);
		current->setPos(0,yPos,0);
		yPos+=current->getY();
	}

	return yPos;
}

