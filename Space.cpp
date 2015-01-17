/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/


#include "Space.h"


Space::Space()
{
}


Space::~Space()
{
}

Space::Space(Point2D p1, Point2D p2, Point2D p3, Point2D p4)
{
	topLeft = p1;
	topRight = p2;
	if (p3.y < p4.y)
	{
		botLeft = p3;
		botRight = { p4.x, p3.y };
	}
	else
	{
		botRight = p4;
		botLeft = { p3.x, p4.y };
	}
	updateDimensions();
}

Space::Space(Point2D p1, Point2D p2, Point2D p3)
{
	this->Update(p1, p2, p3);
}

Space::Space(Point2D p1, int width, int length)
{
	topLeft = p1;
	topRight = { p1.x + width, p1.y };
	botLeft = { p1.x, p1.y + length };
	botRight = { p1.x + width, p1.y + length };
	updateDimensions();
}

void Space::Update(Point2D p1, Point2D p2, Point2D p3)
{
	topLeft = p1;
	topRight = p2;
	botLeft = p3;
	botRight = { p2.x, p3.y };
	updateDimensions();
}

void Space::updateDimensions()
{
	surface = (topRight.x - topLeft.x)*(botLeft.y - topLeft.y);
	length = botLeft.y - topLeft.y;
	width = topRight.x - topLeft.x;
}