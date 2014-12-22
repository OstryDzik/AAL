#include <iostream>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#include "Scena.h"

static bool g_bButtonLDown = false;
static bool g_bButtonRDown = false;

static Obszar* allObszar;
static std::vector<Figura*>* allCubs;
static int allCubsN;

static GLfloat rotation_y = 0.0;
static GLfloat rotation_x = 0.0;
static GLfloat eye_x = 0.0;
static GLfloat eye_y = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static int g_xClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

void DrawSurface(float sizeX, float sizeY)
{
	sizeX /= 2.0;
	sizeY /= 2.0;

	glPushMatrix();

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glVertex3f(sizeX, sizeY, 0);    // Top Right Of The Quad (Top)
	glVertex3f(-sizeX, sizeY, 0);    // Top Left Of The Quad (Top)
	glVertex3f(-sizeX, sizeY, 0);    // Bottom Left Of The Quad (Top)
	glVertex3f(sizeX, sizeY, 0);    // Bottom Right Of The Quad (Top)
	glEnd();

	glPopMatrix();
}

void rysujFigure(float sizeX, float sizeY, float sizeZ)
{
//	sizeX /= 2.0;
//	sizeY /= 2.0;
//	sizeZ /= 2.0;

	glPushMatrix();

	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(1.0);

	glPopMatrix();
}

float* Scena::getRandomColor()
{
	int choice = rand() % 3;
	int choice2 = (choice + 1) % 3;
	int choice3 = (choice + 2) % 3;

	float* result = new float[3];

	result[choice] = float((rand() % 30 + 70) / 100.0);
	result[choice2] = float((rand() % 50 + 30) / 100.0);
	result[choice3] = float((rand() % 20 + 30) / 100.0);

	return result;
}

void RenderObjects(void)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix(); // skalowanie
		glScalef(GLOBAL_SCALE,GLOBAL_SCALE,GLOBAL_SCALE);
		glRotatef(rotation_y, 1, 0, 0);
		glRotatef(rotation_x, 0, 1, 0);

		glPushMatrix(); // tacka
//			glColor3f(1.0, 0.0, 0.0);
			glColor4f(1.0, 0.0, 0.0, 0.5);
			glTranslatef(0.0, -1.0, 0.0);
			rysujFigure(float(allObszar->getRozmiarX()), 1.0, float(allObszar->getRozmiarZ()));
		glPopMatrix(); // tacka

		glPushMatrix();
			glTranslatef(-float(allObszar->getRozmiarX()>>1), 0.0, -float(allObszar->getRozmiarZ()>>1));
			// prostopadłościany
			for (int i = 0; i < allCubsN; i++)
			{
				Figura* current = allCubs->at(i);
				glPushMatrix();
					glColor4f(current->color[0], current->color[1], current->color[2], BOX_ALPHA);
					glTranslatef(float(current->getPosX()+(current->getX()>>1)), float(current->getPosY()+(current->getY()>>1)), float(current->getPosZ()+(current->getZ()>>1)));
					rysujFigure(float(current->getX()), float(current->getY()), float(current->getZ()));
				glPopMatrix();
			}
		glPopMatrix();

	glPopMatrix(); // skalowanie
}

void display(void)
{
	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, -g_fViewDistance, 0, 0, 0, 0, 1, 0);

	// Set up the stationary light
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

	// Render the scene
	RenderObjects();

	// Make sure changes appear onscreen
	glutSwapBuffers();

	fflush(stdout);
}

void reshape(GLint width, GLint height)
{
	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float) g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glMaterialfv(GL_FRONT, GL_AMBIENT, g_lightPos);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.

	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButtonLDown = (state == GLUT_DOWN) ? true : false;
		g_yClick = y + rotation_y;
		g_xClick = x - rotation_x;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		g_bButtonRDown = (state == GLUT_DOWN) ? true : false;
		g_yClick = y - ZOOM_SPEED * g_fViewDistance;
	}
}

void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.

	if (g_bButtonLDown)
	{
		rotation_x = (x - g_xClick);
		rotation_y = -(y - g_yClick);
		glutPostRedisplay();
	}
	else if (g_bButtonRDown)
	{
		g_fViewDistance = (y - g_yClick) / ZOOM_SPEED;
		if (g_fViewDistance < VIEWING_DISTANCE_MIN)
			g_fViewDistance = VIEWING_DISTANCE_MIN;
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	int step = 10;
	switch (key)
	{
	case 27:             // ESCAPE key
		glutLeaveMainLoop();
		break;
	case 'w':
		eye_y += step;
		break;
	case 's':
		eye_y -= step;
		break;
	case 'a':
		eye_x += step;
		break;
	case 'd':
		eye_x -= step;
		break;
	}
	glutPostRedisplay();
}

void Scena::start(int argc, char** argv, Obszar* obszar)
{
	g_lightPos[0] = -obszar->getRozmiarX()*2;
	g_lightPos[2] = -obszar->getRozmiarZ()*2;
	allObszar = obszar;
	allCubs = obszar->getFigury();
	allCubsN = obszar->getLiczbaFigur();

	// GLUT Window Initialization:
	glutInit(&argc, argv);
	glutInitWindowSize(g_Width, g_Height);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Projekt AAL");

	// Initialize OpenGL graphics state
	InitGraphics();

	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	for (int i = 0; i < allCubsN; i++)
	{
		allCubs->at(i)->color = Scena::getRandomColor(); // przypisanie losowych kolorów
	}

	// Turn the flow of control over to GLUT
	glutMainLoop();
}

void Scena::close()
{

}

