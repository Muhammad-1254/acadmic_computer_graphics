#include <fstream>
#include <windows.h> // Include for Windows systems
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

using namespace std;

//number_of_polylines
//number_of_points_in_polyline_1
//x1 y1
//x2 y2
//...
//number_of_points_in_polyline_2
//x1 y1
//x2 y2


void drawPolyLineFile(const char* fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // open the file
	if (inStream.fail())
		return;
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set text color to white
	drawPolyLineFile("C:\\Users\\Muhammad Umar\\source\\repos\\DrawingDino\\DinoPolylines.txt");
    glFlush();
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500);
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

