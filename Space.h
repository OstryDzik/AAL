/*
* Autor: Filip £êczycki
*
* 3D Bin Packing Problem Solver
*/

#pragma once


typedef struct point
{
	int x;
	int y;
}Point2D;

//klasa pomocnicza, s³u¿¹ca do reprezentacji prostok¹tnego miejsca w przestrzeni
class Space
{
public:
	Space();
	Space(Point2D p1, Point2D p2, Point2D p3, Point2D p4);
	Space(Point2D p1, Point2D p2, Point2D p3);
	Space(Point2D p1, int width, int length);
	~Space();
	void updateDimensions();
	void Update(Point2D p1, Point2D p2, Point2D p3);
	int getSurface()
	{
		return surface;
	}
	Point2D getTopLeft()
	{
		return topLeft;
	}
	Point2D getTopRight()
	{
		return topRight;
	}
	Point2D getBotLeft()
	{
		return botLeft;
	}
	Point2D getBotRight()
	{
		return botRight;
	}

	int getLength()
	{
		return length;
	}

	int getWidth()
	{
		return width;
	}


private:
	int surface;
	int length;
	int width;
	Point2D topLeft;
	Point2D topRight;
	Point2D botLeft;
	Point2D botRight;
};

