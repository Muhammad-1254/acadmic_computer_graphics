#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <gl/freeglut.h>
#include "wav.h"
#include "Background.h"
#include "Utility.h"

float screenWidth = 640;
float screenHeight = 480;

Background bg(0, 0);

int sleepFrame = 1;
bool sleep = true;

float ghostX = rand() % 440 + 100;
float ghostY = rand() % 480 + 150;

void myTimer(int value)
{
		ghostX = rand() % 440 + 100;
		ghostY = rand() % 330;
		
		if (!(sleep)) sleepFrame = rand() % 2 + 1;

		Utility::draw(ghostX,ghostY);
		int time = rand() % 2000 + 1500;

		glutPostRedisplay();
		glutTimerFunc(time, myTimer, 1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bg.render();
	
	if (sleepFrame == 0) {
		Utility::draw(ghostX, ghostY);
		PlayForegroundSound("jumpscare1.wav");
		sleep = false;
	}
	else {
		sleepFrame--;
		sleep = true;
	}
	
	std::cout << sleep << std::endl;
	glutSwapBuffers();
	GLenum err;
}

void myInit(void)
{
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

	PlayBackgroundSound("horrorbg.wav");
	//D:\\Stuff\\Uni Stuff\\SEM 6\\Computer Graphics\\LABS\\Visual Studio C++\\Ghost\\Ghost
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glViewport(0, 0, screenWidth, screenHeight);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("Ghost");

	glutDisplayFunc(display);

	myInit();
	glutTimerFunc(500, myTimer, 1);
	glutMainLoop();

	return 0;
}