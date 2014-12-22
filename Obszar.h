/*
 * Obszar.h
 *
 *  Created on: 23 lis 2014
 *      Author: marcin
 */

#ifndef OBSZAR_H
#define OBSZAR_H

#include <iostream>
#include <vector>
#include "Figura.h"

class Obszar
{
public:
	Obszar(int rozmiarX, int rozmiarY);
	virtual ~Obszar();

	void generuj(int N, int minA, int maxA);
	void wyczysc();

	int algorithmTrivial();

	//gettery

	int getRozmiarX()
	{
		return rozmiarX;
	}

	int getRozmiarZ()
	{
		return rozmiarZ;
	}

	int getLiczbaFigur()
	{
		return liczbaFigur;
	}

	std::vector<Figura*>* getFigury()
	{
		return &figury;
	}

private:
	int rozmiarX, rozmiarZ; // wymiary obszaru
	int liczbaFigur;
	std::vector<Figura*> figury;

	void setOptimalHeight(Figura* figura);
};

#endif /* OBSZAR_H */
