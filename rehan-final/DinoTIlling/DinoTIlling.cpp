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
	/*glClear(GL_COLOR_BUFFER_BIT); */// we dont clear the screen in this code 
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
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}
//void setViewport(float left, float right, float bottom, float top)
//{
//	glViewport(left, bottom, right - left, top - bottom);
//}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	setWindow(0, 640.0, 0, 480.0);
	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			glViewport(i * 140, j * 94, 164, 104);
			glColor3f(0.0, 0.0, 0.0); // Set the drawing color to black

			drawPolyLineFile("C:\\Users\\Muhammad Umar\\source\\repos\\DrawingDino\\DinoPolylines.txt");
		}
	}
	//drawPolyLineFile("C:\\Users\\Muhammad Umar\\source\\repos\\DrawingDino\\DinoPolylines.txt");
	glFlush();
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 80, 0, 10); this is not using here
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Text Rendering Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

