// Projekt4.cpp : Defines the entry point for the console application.
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

GLfloat x = 130.0f;
GLfloat y = 130.0f;

GLsizei radiusSizeOfPolygon = 100;

int numberOfSides = 9;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

int width = 800;
int height = 600;

GLfloat windowWidth;
GLfloat windowHeight;

GLfloat a = x;
GLfloat b = y;
GLfloat r = 0;
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
float max(float * Array)
{
	float max = Array[0];
	for (int i = 1; i < numberOfSides; i++)
	{
		if (max < Array[i])
		{
			max = Array[i];
		}
	}

	return max;
}
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(128.0f, 0.9f, 0.0f);

	glBegin(GL_POLYGON);
	r = r >= 9.2 ? 0 : r;

	for (int i = 0; i < numberOfSides; i++)
	{
		float xx = x + radiusSizeOfPolygon * sin(2.0*M_PI*i / numberOfSides);
		float yy = y + radiusSizeOfPolygon * cos(2.0*M_PI*i / numberOfSides);

		float x_rot = a + (xx - a)*cos(r) - (yy - b)*sin(r);
		float y_rot = b + (xx - a)*sin(r) + (yy - b)*cos(r);

		_X[i] = x_rot;
		_Y[i] = y_rot;
		glVertex2f(x_rot, y_rot);
	}
	r += 0.01f;
	glEnd();
	glutSwapBuffers();
}

void TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void SetupRC() {
	glClearColor(57.6f, 0.4f, 0.12f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}

	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void AppCall(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Program 4");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	delete _X;
	delete _Y;
}
void main(int argc, char* argv[]) {
	AppCall(argc, argv);
}
