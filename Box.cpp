#include <iostream>
#include <stdlib.h>
#include "Box.h"

// Konstruktor, zawiera długości boków
Box::Box(int a, int b, int c, int ID)
{
	setDimens(a, b, c);
	this->clearPosition();
	this->ID = ID;
}

// Domyślny konstruktor
Box::Box()
{
	setDimens(0, 0, 0);
	this->clearPosition();
}

Box::Box(Box* box)
{
	Box();
	this->setDimens(box->getInitX(), box->getInitY(), box->getInitZ());
	this->posX = box->getPosX();
	this->posY = box->getPosY();
	this->posZ = box->getPosZ();
	this->actualRotation = box->getRotation();
	this->color = box->getColor();
	this->ID = box->getID();
}


void Box::setDimens(int a, int b, int c)
{
	this->x = a;
	this->y = b;
	this->z = c;
	this->volume = a*b*c;
	if (x*y <= y*z && x*y <=x*z)
	{
		this->minSurface = x*y;
	}
	else if (y*z<=x*y && y*z <= x*z)
	{
		this->minSurface = y*z;
	}
	else
	{
		this->minSurface = x*z;
	}
}

void Box::setPos(int x, int y, int z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

void Box::setPos(Position pos)
{
	this->posX = pos.x;
	this->posY = pos.y;
	this->posZ = pos.z;
}

// Destruktor
Box::~Box()
{

}

void Box::clearPosition()
{
	this->actualRotation = ROTATION_0;
	this->posX = 0;
	this->posY = 0;
	this->posZ = 0;
}

std::string Box::printBox()
{
	std::string box;
	box += ("BoxID: " + std::to_string(ID)+ "\n");
	box += ("Position (x,y,z): " + std::to_string(posX) + "," + std::to_string(posY) + ","+ std::to_string(posZ)+ "\n");
	box += ("Size (w,h,l): " + std::to_string(this->getInitX()) + "," + std::to_string(this->getInitY()) + "," + std::to_string(this->getInitZ())+ "\n");
	return box;
}

