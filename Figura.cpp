#include <iostream>
#include <stdlib.h>
#include "Figura.h"

// Konstruktor, zawiera długości boków
Figura::Figura(int a, int b, int c)
{
	setDimens(a, b, c);
	this->clearPosition();
}

// Domyślny konstruktor
Figura::Figura()
{
	setDimens(0, 0, 0);
	this->clearPosition();
}

void Figura::setDimens(int a, int b, int c)
{
	this->x = a;
	this->y = b;
	this->z = c;
}

void Figura::setPos(int x, int y, int z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

// Destruktor
Figura::~Figura()
{

}

void Figura::clearPosition()
{
	this->actualRotation = ROTATION_0;
	this->posX = 0;
	this->posY = 0;
	this->posZ = 0;
}

void Figura::printDimens()
{
	std::cout << this->x << "x" << this->y << "x" << this->z;
}

