
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#include <gl/freeglut.h>
#include "pixMap.h"
#include "Mario.h"
#include "wav.h"
#include "spider.h"
#include "ParametricShapes.h"

// Global variables
int screenWidth = 640;
int screenHeight = 480;

Mario m(Point2(10, 100));
Spider s(250.0f,240.0f);
Triangle t(35,200,20, 20);
Circle c(600,400,30);
RectanglE r(600,370,25,50);
RectanglE r1(0, 0, 200, 1280);

clock_t lastKeyPressTime = 0;
const int IDLE_TIMEOUT_MS = 300;
int lastKeyPressed = 3;

void myTimer(int value)
{

	// Redisplay the current frame
	r.changePosition(-5, 0);
	c.changePosition(-3, 3);

	if (lastKeyPressed == 0) {
		clock_t currentTime = clock();
		lastKeyPressTime = currentTime;
		m.changePosition(-10, 0);
		t.changePosition(-10, 0);
	}
	else if (lastKeyPressed == 1) {
		clock_t currentTime = clock();
		lastKeyPressTime = currentTime;
		m.changePosition(10, 0);
		t.changePosition(10, 0);
	}
	else if (lastKeyPressed == 3) {
		m.changeMode(Mario::STAY);

	}

	// Schedule the next timer call after 33 milliseconds (1000 ms / 30 fps)
	glutPostRedisplay();
	glutTimerFunc(100, myTimer, 1);
}

void idle(void)
{
	clock_t currentTime = clock();
	double elapsedTime = double(currentTime - lastKeyPressTime) / CLOCKS_PER_SEC * 1000;

	if (elapsedTime >= IDLE_TIMEOUT_MS) {
		lastKeyPressed = 3;
		lastKeyPressTime = currentTime;
		std::cout << "TIMER FUNCTION RUN" << currentTime << " " << elapsedTime << std::endl;
	}
}

void renderText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_18) {
	glRasterPos2f(x, y);
	for (const char* c = text; *c != '\0'; ++c) {
		glutBitmapCharacter(font, *c);
	}
}

void myInit(void)
{
	// background color to blue
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f,1.0f);
		
	//PlayBackgroundSound("Music.wav");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f); // Set text color to black
	renderText(300.0f, 460.0f, "Mario");

	c.render();
	glColor3f(0.0f, 0.48f, 0.0f); // setting color for ground
	r1.render();
	glColor3f(173.0f / 255.0f, 216.0f / 255.0f, 230.0f / 255.0f); // green color for cloud
	r.render();
	s.render();
	m.render();
	glColor3f(0.0f, 0.0f, 0.0f); // for triangle above mario
	t.render();

	glutSwapBuffers();
	GLenum err;
	
}

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 's':
		lastKeyPressTime = clock();
		m.changeMode(Mario::STAY);
		break;
	case 'p':
		lastKeyPressTime = clock();
		m.changeMode(Mario::RUN);
		break;
	case 'j':
		lastKeyPressTime = clock();
		m.changeMode(Mario::JUMP);
		break;
	case 'r':
		m.changeMode(Mario::STAY);
		m.setPosition(10, 100);
		t.setPosition(35, 200);
		r.setPosition(600, 370);
		c.setPosition(600, 400);
		break;
	}
	glutPostRedisplay();
}
void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lastKeyPressTime = clock();
		m.changeMode(Mario::RUN);
		lastKeyPressed = 0;
	
		break;

	case GLUT_KEY_RIGHT:
		lastKeyPressTime = clock();
		m.changeMode(Mario::RUN);
		lastKeyPressed = 1;
		break;

	case GLUT_KEY_UP:
		lastKeyPressTime = clock();
		lastKeyPressed = 2;
		m.changeMode(Mario::JUMP);
		break;

	case GLUT_KEY_DOWN:

		break;
	}

}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lastKeyPressTime = clock();
		lastKeyPressed = 3;

		break;

	case GLUT_KEY_RIGHT:
		lastKeyPressTime = clock();
		lastKeyPressed = 3;
		break;

	case GLUT_KEY_UP:
		lastKeyPressTime = clock();
		lastKeyPressed = 3;
		break;

	case GLUT_KEY_DOWN:
		lastKeyPressTime = clock();
		lastKeyPressed = 3;
		break;
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glViewport(0, 0, screenWidth, screenHeight);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("MY Mario");


	glutDisplayFunc(display);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	glutIdleFunc(idle);
	glutTimerFunc(100,myTimer,1);
	glutMainLoop();

	return 0;
}