#include <fstream>
#include <windows.h> // Include for Windows systems
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

using namespace std;

float zoomFactor = 1.0f; // Global variable to track zoom level

void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float centerX = 800 / 2.0f;
    float centerY = 500 / 2.0f;
    gluOrtho2D(centerX - (centerX / zoomFactor), centerX + (centerX / zoomFactor),
        centerY - (centerY / zoomFactor), centerY + (centerY / zoomFactor));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        zoomFactor *= 1.1f; // Zoom in (increase zoomFactor)
        break;
    case '-':
        zoomFactor /= 1.1f; // Zoom out (decrease zoomFactor)
        break;
    case 'q':
        exit(0);
    }
    setProjection(); // Update the projection matrix based on zoom level
    glutPostRedisplay(); // Redisplay to reflect the changes
}

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
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
    drawPolyLineFile("C:\\Users\\Muhammad Umar\\source\\repos\\DrawingDino\\DinoPolylines.txt");
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    setProjection(); // Set initial projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Dino Zooming Example");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}
