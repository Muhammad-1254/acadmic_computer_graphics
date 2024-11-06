#include <iostream>
#include "gl/glut.h"
#define PI 3.141592
float thetha = 0;
float planeX = 0.0f, planeY = 0.0f, planeAngle = 0.0;
bool hasCrashed = false;
bool crashedAnimation = false;
int crashCounters = 20;
int crashBounces = 5;

void display(void);
void drawWind(void);
void drawwindmill(void);
void drawplane();
void drawlandscape();
void Timer(int value);
void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawlandscape();
	drawplane();
	drawwindmill();

	glutSwapBuffers();
}

void drawWind()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(125.0, 90.0);
	glVertex2f(140.0, 120.0);
	glVertex2f(160.0, 120.0);
	glEnd();
}

void drawwindmill()
{
	glPushMatrix();

	for (int i = 0; i < 360; i += 90)
	{
		float angle = i + thetha;
		glPushMatrix();
		glTranslatef(125, 90, 0);
		glRotatef(-angle, 0, 0, 1);
		glTranslatef(-125, -90, 0);

		drawWind();
		glPopMatrix();
	}
	glPopMatrix();
}

void Timer(int value)
{
	// Rotate windmill
	thetha += 1.5f;
	if (thetha > 360) thetha = 0;

	
	if (!hasCrashed)
	{
		planeX -= 2.5f;
		planeY -= 5.0f;
		// Check for collision (when plane gets close to windmill)
		if (planeY <= -180)
		{
			hasCrashed = true;

			std::cout << "Plane has crashed!" << std::endl;
		}
	}
	if (hasCrashed && crashCounters > 0) {
		// if  crashBounces even than spaceY increase else spaceY decrease
		planeX -= 5.0f;
		if (crashBounces >= 0) {
		if (crashBounces % 2 == 0)
			planeY += 2.0f;
		else
			planeY -= 2.0f;
		}
		else {
			planeAngle += 5.0f;
		}
		crashBounces--;
		crashCounters--;

	}


	// Redraw the scene
	display();

	// Keep calling Timer function to update animation
	glutTimerFunc(30, Timer, 1);
}

void drawplane()
{
	glPushMatrix();

	// Translate plane to its new position and rotate
	glTranslatef(planeX, planeY, 0);
	glRotatef(planeAngle, 0, 0, 1);
	//glTranslatef(planeX, planeY, 0);

	/* Draw a plane */
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(245.0, 230.0);
	glVertex2f(245.0, 240.0);
	glVertex2f(215.0, 230.0);

	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(244.0, 228.0);
	glVertex2f(244.0, 235.0);
	glVertex2f(228.0, 235.0);
	glEnd();

	glPopMatrix();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1000, 720);
	glutCreateWindow("BSCS 514 Lab #8");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(30, Timer, 1);
	glutMainLoop();
}

void drawlandscape()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(250.0, 0.0);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2f(250.0, 50.0);
	glColor3f(0.0, 0.8, 0.0);
	glVertex2f(0.0, 50.0);
	glColor3f(0.0, 0.7, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 0.6);
	glVertex2f(250.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(200.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(150.0, 50.0);

	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(200.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(150.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(100.0, 50.0);

	glColor3f(0.0, 0.0, 0.7);
	glVertex2f(150.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(100.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(50.0, 50.0);

	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(100.0, 50.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(50.0, 150.0);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2f(0.0, 50.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.0);
	glVertex2f(145.0, 50.0);
	glVertex2f(135.0, 100.0);
	glVertex2f(115.0, 100.0);
	glVertex2f(105.0, 50.0);
	glEnd();
}

void init()
{
	glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 250.0, 0.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 250.0, 0.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(0);
}
