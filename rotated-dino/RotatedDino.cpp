#include <fstream>
#include <windows.h> // Include for Windows systems
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

using namespace std;

void drawPolyLineFile(const char* fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // open the file
	if (inStream.fail())
		return;
	GLint numpolys, numLines, x, y;
	inStream >> numpolys; // read the number of polylines
	for (int j = 0; j < numpolys; j++) // read each polyline
	{
		inStream >> numLines;
		glBegin(GL_LINE_STRIP); // draw the next polyline
		for (int i = 0; i < numLines; i++)
		{
			inStream >> x >> y; // read the next x, y pair
			glVertex2i(x, y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();
}

void drawDinosaur()
{
	glPushMatrix();
	glScalef(0.2f, 0.2f, 1.0f); // Scale down the dinosaur
	drawPolyLineFile("C:\\Users\\Muhammad Umar\\source\\repos\\DrawingDino\\DinoPolylines.txt");
	glPopMatrix();
}

//void drawCircleWithDinosaurs()
//{
//	float radius = 185.0f;  
//	int numDinosaurs = 12;  
//
//	for (int i = 0; i < numDinosaurs; ++i)
//	{
//		float theta = 2.0f * 3.1415926f * float(i) / float(numDinosaurs); // Calculate angle for each dinosaur
//		float x = radius * cosf(theta); 
//		float y = radius * sinf(theta); 
//
//		glPushMatrix();
//		glTranslatef(400 + x, 300 + y, 0); 
//		glRotatef(0, 0, 0, 1); 
//		drawDinosaur(); 
//		glPopMatrix();
//	}
//}

void drawCircleWithDinosaurs()
{
	float radius = 185.0f;  
	int numDinosaurs = 12;  

	for (int i = 0; i < numDinosaurs; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(numDinosaurs); 
		float x = radius * cosf(theta); 
		float y = radius * sinf(theta); 
		glPushMatrix();
		glTranslatef(400 + x, 300 + y, 0); 
		glRotatef(theta * 180 / 3.14159f + 250, 0, 0, 1); 
		drawDinosaur(); 
		glPopMatrix();
	}
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawCircleWithDinosaurs();
    glFlush();
}


void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1500, 1000);
	glutCreateWindow("Text Rendering Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}