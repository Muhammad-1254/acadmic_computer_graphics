#include <GL/glew.h>  // Include GLEW before OpenGL headers
#include <GL/gl.h>
#include <gl/freeglut.h>
#include "Spider.h"
#include "Bullet.h"
#include "Bullet1.h"
#include "wav.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int screenWidth = 640;
int screenHeight = 480;

float angle = 90.0f;
bool gameOver = false;

float mouseX = 0;
float mouseY = 0;
bool bullet_fired_using_mouse = false;
float speed = 0;
int frame = 0;

float initialBullettX = 304;
float initialBulletY = 30;

//float X = std::rand() % 640;
//float Y = std::rand() % 480;
float X = 0;
float Y = 0;

Spider mainSpider(Point2(X, Y));
//Bullet bullet(initialBullettX, initialBulletY);
Bullet1 bullet(initialBullettX, initialBulletY, "bullet3.bmp");

float bulletDx = mouseX - bullet.get_x();
float bulletDy = mouseY - bullet.get_y();

void myTimer(int value)
{
	if (gameOver) 
	{
		/*bullet.bX = 640;
		bullet.bY = 480;*/

		bullet.bX = initialBullettX;
		bullet.bY = initialBulletY;

		glutPostRedisplay();
		glutTimerFunc(100, myTimer, 1);
	}
	// giving random movement to spider
	else 
	{
		if (frame % 3 == 0) {
			float dx = std::rand() % 16 - 8;
			float dy = std::rand() % 16 - 8;
			mainSpider.changePosition(dx, dy);
			mainSpider.run();
		}

		float distanceX = mainSpider.spider_getX() + 32  - bullet.get_x();
		float distanceY = mainSpider.spider_getY() + 32 - bullet.get_y();

		float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

		bullet.changePos(bulletDx * speed, bulletDy * speed);

		//std::cout << distance << std::endl;
		//std::cout << (((distance < 90.0f) && (bullet.bX >= mainSpider.spider_getX() - 20) && (bullet.bY >= mainSpider.spider_getY() - 20)) || (distance < 6.0f));
		
		if (distance < 80.0f) {
			mainSpider.changeMode(Spider::DIE);
			gameOver = true;
			bullet.bX = initialBullettX;
			bullet.bY = initialBulletY;
			bulletDx = 304 - bullet.get_x();
			bulletDy = 480 - bullet.get_y();
			angle = angle = std::atan2(bulletDy, bulletDx) * 180.0f / 3.14;
			//PlayForegroundSound("Music.wav");
		}

		// for bullet rotation
		angle = std::atan2(bulletDy, bulletDx) * 180.0f / 3.14;

		if ((bullet.bX > 640) || (bullet.bX < 0) || (bullet.bY > 480) || (bullet.bY < 0)) {
			bullet.is_fired = false;
			bullet.bX = initialBullettX;
			bullet.bY = initialBulletY;
			speed = 0;
		}

		if ((bullet.bX > 640) || (bullet.bX < 0) || (bullet.bY > 480) || (bullet.bY < 0)) {
			bullet.is_fired = false;
			bullet.bX = initialBullettX;
			bullet.bY = initialBulletY;
			speed = 0;
		}

		glutPostRedisplay();
		glutTimerFunc(32, myTimer, 1);
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
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

	//PlayBackgroundSound("bk1.wav");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 640, 0, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void myMouseHandler(int button, int state, int x, int y) {
	// If the left button is clicked and the button state is GLUT_DOWN
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (!(bullet.is_fired)) {

			bullet.is_fired = true;
			mouseX = x; // Store the x-coordinate of the mouse click
			mouseY = screenHeight - y; // Store the y-coordinate (invert y-axis for OpenGL)

			//bullet_fired_using_mouse = true;
			bulletDx = mouseX - bullet.bX;
			bulletDy = mouseY - bullet.bY;
			speed = 0.09 / 3;
			PlayForegroundSound("Shoot.wav");
		}
	}
}


void display(void)
{

	frame ++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mainSpider.render();

	bullet.rotationAngle = angle + 90;
	//glEnable(GL_TEXTURE_2D);
	bullet.render();
	//glDisable(GL_TEXTURE_2D);

	GLenum err1 = glGetError();
	if (err1 != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << err1 << std::endl;
	}

	glColor3f(0.0f, 0.0f, 0.0f); // Set text color to black
	renderText(300.0f, 460.0f, "Spider Shooter");

	glutSwapBuffers();
	GLenum err;

}

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 's':

		break;
	case 'p':
		
		break;
	case 'j':
		
		break;
	case 'r':
		mainSpider.changeMode(Spider::RUN);
		mainSpider.setPosition(std::rand() % 576, std::rand() % 316 + 100);
		bullet.bX = initialBullettX;
		bullet.bY = initialBulletY;
		bullet.is_fired = false;
		gameOver = false;
		speed = 0;
		break;
	}
}

void passiveMotion(int x, int y) {
	// Update mouse coordinates
	if (bullet.is_fired) return;
	if (gameOver) return;
	mouseX = x;
	mouseY = screenHeight - y;
	angle = std::atan2(bulletDy, bulletDx) * 180.0f / 3.14;
	bulletDx = mouseX - bullet.get_x();
	bulletDy = mouseY - bullet.get_y();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glViewport(0,0,screenWidth,screenHeight);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("Spider Shooter");

	glutDisplayFunc(display);
	glutKeyboardFunc(myKB_Handler);
	glutMouseFunc(myMouseHandler);
	glutPassiveMotionFunc(passiveMotion);

	myInit();
	glutTimerFunc(32, myTimer, 1);
	glutMainLoop();

	return 0;
}