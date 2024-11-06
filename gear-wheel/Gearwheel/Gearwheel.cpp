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

void drawGearCircle()
{
	float radius = 50.0f;
	int numSegments = 100;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numSegments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawGearTooth()
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, -24+24);
	glVertex2f(12.8, -14.4+24);
	glVertex2f(38.4, -14.4+24);
	glVertex2f(38.4, 14.4+24);
	glVertex2f(12.8, 14.4+24);
	glVertex2f(0, 24+24);
	glEnd();
}

void drawGearWheel()
{
	double rad = 6.0 * PI / 180;
	float sin6 = radius * sin(rad);
	float cos6 = radius * cos(rad);
	
	glPushMatrix();

	glTranslatef(cos6, -sin6, 0);
	for (int i = 0; i < 360; i += 9) 
	{
		float angle = i + thetha;
		glPushMatrix();
		
		glTranslatef(-cos6, sin6, 0);
		glRotatef(-angle, 0, 0, 1);
		glTranslatef(cos6, -sin6, 0);
		drawGearTooth();
		
		glPopMatrix();
	}

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	drawBackground();
	drawGearCircle();
	drawGearWheel();
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