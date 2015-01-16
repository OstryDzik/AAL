/*
* Autor: Filip Łęczycki
*
* 3D Bin Packing Problem Solver
*/

#ifndef BOX_H
#define BOX_H
// możliwe jest 6 typów rotacji
//
// (obrót = zamiana współrzędnych)
//
// 0: x->x, y->y, z->z
// 1: x->x, y->z, z->y
// 2: x->y, y->x, z->z
// 3: x->z, y->y, z->x
// 4: x->y, y->z, z->x
// 5: x->z, y->x, z->y
//
#include <string>

typedef struct pos
{
	int x;
	int y;
	int z;
} Position;

typedef enum Rotacja
{
	ROTATION_0, ROTATION_1, ROTATION_2, ROTATION_3, ROTATION_4, ROTATION_5
} Rotation;


class Box
{
public:
	Box(int a, int b, int c, int ID); // konstruktor
	Box(Box* box); //konstruktor kopiujący;
	Box(); // konstruktor
	virtual ~Box(); // destruktor
	void setDimens(int a, int b, int c); // ustawia rozmiar
	std::string printBox(); // wypisuje pozycję i rozmiar pudelka
	void clearPosition();

	void setPos(int x, int y, int z);
	void setPos(Position pos);

	void setRotation(Rotation rot)
	{
		this->actualRotation = rot;
	}

	// wymiary po obrocie
	int getX()
	{
		switch (actualRotation)
		{
		case ROTATION_0:
		case ROTATION_1:
			return x;
		case ROTATION_2:
		case ROTATION_4:
			return y;
		case ROTATION_3:
		case ROTATION_5:
			return z;
		}
		return -1;
	}
	int getY()
	{
		switch (actualRotation)
		{
		case ROTATION_0:
			return y;
		case ROTATION_3:
			return y;
		case ROTATION_1:
			return z;
		case ROTATION_4:
			return z;
		case ROTATION_2:
			return x;
		case ROTATION_5:
			return x;
		}
		return -1;
	}
	int getZ()
	{
		switch (actualRotation)
		{
		case ROTATION_0:
			return z;
		case ROTATION_2:
			return z;
		case ROTATION_1:
			return y;
		case ROTATION_5:
			return y;
		case ROTATION_3:
			return x;
		case ROTATION_4:
			return x;
		}
		return -1;
	}
	int getPosX()
	{
		return posX;
	}
	int getPosY()
	{
		return posY;
	}
	int getPosZ()
	{
		return posZ;
	}

	int getVolume()
	{
		return volume;
	}

	int getMinSurface()
	{
		return minSurface;
	}
	int getSurface()
	{
		return getX()*getZ();
	}
	int getID()
	{
		return ID;
	}
	int getInitX()
	{
		return x;
	}
	int getInitY()
	{
		return y;
	}
	int getInitZ()
	{
		return z;
	}
	Rotation getRotation()
	{
		return actualRotation;
	}
	float* getColor()
	{
		return color;
	}
	void setColor(float* color)
	{
		this->color = color;
	}
protected:
private:
	int ID;
	float* color;
	int x, y, z; // długości boków
	int minSurface;
	int posX;
	int posY;
	int posZ;
	Rotacja actualRotation;
	int volume;
};

#endif // BOX_H
