// Projekt2i3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

GLfloat x = 0.0f;
GLfloat y = 30.0f;
GLsizei radiusSizeOfPolygon = 25;

int numberOfSides = 9;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

int width = 800;
int height = 600;

GLfloat windowWidth;
GLfloat windowHeight;

float * _X = new float[numberOfSides];
float * _Y = new float[numberOfSides];

float min(float * Array)
{
	float min = Array[0];

	for (int i = 1; i < numberOfSides; i++)
	{
		if (min > Array[i])
		{
			min = Array[i];
		}
	}
	return min;
}

float max(float * inArray)
{

	float max = inArray[0];

	for (int i = 1; i < numberOfSides; i++)
	{
		if (max < inArray[i])
		{
			max = inArray[i];
		}
	}
	return max;
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(192.0f, 0.0f, 48.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < numberOfSides; i++)
	{
		float xx = x + radiusSizeOfPolygon * sin(2.0*M_PI*i / numberOfSides);
		float yy = y + radiusSizeOfPolygon * cos(2.0*M_PI*i / numberOfSides);

		_X[i] = xx;
		_Y[i] = yy;
		glVertex2f(xx, yy);
	}
	glEnd();
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	float minX = min(_X);
	float maxX = max(_X);
	float minY = min(_Y);
	float maxY = max(_Y);

	if (x > windowWidth - radiusSizeOfPolygon || x < radiusSizeOfPolygon)
		xstep = -xstep;

	if (y > windowHeight - radiusSizeOfPolygon || y < radiusSizeOfPolygon - minY)
		ystep = -ystep;

	x += xstep;
	y += ystep;

	glutReshapeWindow(width, height);
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 10);
}

void SecondTimerFunction(int value)
{
	float minFromX = min(_X); // left
	float maxFromX = max(_X); // rigth
	float minFromY = min(_Y); // bottom
	float maxFromY = max(_Y); // top

	bool leftRigthCollision = x > windowWidth - radiusSizeOfPolygon || x < radiusSizeOfPolygon;
	bool topBottomCollision = y > windowHeight - radiusSizeOfPolygon || y < radiusSizeOfPolygon - minFromY;

	if (y > windowHeight - radiusSizeOfPolygon)
	{
		ystep = 0;
	}

	if (x > windowWidth - radiusSizeOfPolygon)
	{
		xstep = 0;
		ystep = -1;
	}

	if (y < radiusSizeOfPolygon - minFromY && x > windowWidth - radiusSizeOfPolygon)
	{
		ystep = 0;
		xstep = -1;
	}

	if (x < radiusSizeOfPolygon &&y < radiusSizeOfPolygon - minFromY)
	{
		xstep = 0;
		ystep = 1;
	}

	if (x < radiusSizeOfPolygon &&y > windowHeight - radiusSizeOfPolygon)
	{
		ystep = 0;
		xstep = 1;
	}

	x += xstep;
	y += ystep;

	glutPostRedisplay();
	glutTimerFunc(50, SecondTimerFunction, 10);
}

void SetupRC()
{
	glClearColor(128.0f, 0.0f, 0.12f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 150.0f*h / w;
		windowWidth = 150.0f;
	}

	else
	{
		windowWidth = 150.0f*w / h;
		windowHeight = 150.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void AppCall(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Program 2 i 3");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(50, TimerFunction, 10);

	SetupRC();

	glutMainLoop();

	delete _X;
	delete _Y;
}

void SecondAppCall(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Program 2 i 3");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(50, SecondTimerFunction, 10);

	SetupRC();

	glutMainLoop();

	delete _X;
	delete _Y;
}
void main(int argc, char* argv[])
{
	SecondAppCall(argc, argv);
}


