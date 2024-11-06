#include <iostream>
#include "gl/glut.h"
#define PI 3.141592

float thetha = 0;
float speed = 0.8;
float centerX = 0;
float centerY = 0;
float radius = 300;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
		exit(0);
		break;
	}
}

void drawBackground()
{
	glBegin(GL_LINES);
	glVertex2f(-640, 0);
	glVertex2f(640, 0);
	glVertex2f(0, -480);
	glVertex2f(0, 480);
	glEnd();
}

void drawStarSingle() {
	glBegin(GL_LINE_LOOP);
	glVertex2f(-1.0f, 23.0f);
	glVertex2f(100.0f, 300.0f);
	glVertex2f(158, 104);
	glVertex2f(123, 105);
	glVertex2f(100 , 190);
	glVertex2f(28, 0.0f);
	glEnd();
}


void drawStarComplete()
{

	glPushMatrix();

	for (int i = 0; i < 360; i += 72)
	{
		//float angle = i + thetha;
		float angle = i;
		glPushMatrix();
		glRotatef(-angle, 0, 0, 1);
		glTranslatef(-92.0f, -17.0f, 0.0f);
		drawStarSingle();

		glPopMatrix();
	}

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	drawBackground();
	drawStarComplete();
	glutSwapBuffers();
}

void Timer(int value)
{
	thetha += speed;
	if (thetha > 360) thetha = 0;
	display();
	glutTimerFunc(30, Timer, 1);
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);

	glutCreateWindow("Gearwheel");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(30, Timer, 1);
	glutMainLoop();
}