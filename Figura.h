#ifndef FIGURA_H
#define FIGURA_H

// możliwe są jest 6 typów rotacji
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

typedef enum Rotacja
{
	ROTATION_0, ROTATION_1, ROTATION_2, ROTATION_3, ROTATION_4, ROTATION_5
} Rotation;

class Figura
{
public:
	Figura(int a, int b, int c); // konstruktor
	Figura(); // konstruktor
	virtual ~Figura(); // destruktor

	void setDimens(int a, int b, int c); // ustawia rozmiar
	void printDimens(); // wyświetla rozmiar
	void clearPosition();

	void setPos(int x, int y, int z);

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
	}
	int getY()
	{
		switch (actualRotation)
		{
		case ROTATION_0:
		case ROTATION_3:
			return y;
		case ROTATION_1:
		case ROTATION_4:
			return z;
		case ROTATION_2:
		case ROTATION_5:
			return x;
		}
	}
	int getZ()
	{
		switch (actualRotation)
		{
		case ROTATION_0:
		case ROTATION_2:
			return z;
		case ROTATION_1:
		case ROTATION_5:
			return y;
		case ROTATION_3:
		case ROTATION_4:
			return x;
		}
	}
	// przeskalowane pozycje
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

	int x, y, z; // długości boków
	int posX;
	int posY;
	int posZ;
	float* color;
protected:
private:
	Rotacja actualRotation;
};

#endif // FIGURA_H
