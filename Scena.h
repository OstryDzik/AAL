#ifndef SCENA_H
#define SCENA_H

#include <vector>
#include "Obszar.h"
#include "Figura.h"

#define BOX_ALPHA 0.6
#define GLOBAL_SCALE 0.2
#define ZOOM_SPEED 1.0
#define VIEWING_DISTANCE_MIN  10.0

typedef struct Size
{
	int x;
	int y;
	int z;
} Size;

class Scena
{
public:
	static void start(int argc, char** argv, Obszar* obszar);
	static void close();
	static float* getRandomColor();
protected:
private:
};

#endif // SCENA_H
