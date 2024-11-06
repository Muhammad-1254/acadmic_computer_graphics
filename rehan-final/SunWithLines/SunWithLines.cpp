#include <windows.h> // For Windows systems
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

void drawCircle(float cx, float cy, float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
}

void drawSun(float cx, float cy, float radius) {
    // Draw the circle (sun)
    drawCircle(cx, cy, radius);

    // Draw rays
    for (int i = 0; i < 20; i++) {
        float angle = i * M_PI / 9; // 45 degrees between rays
        float x1 = cx + radius * cos(angle);
        float y1 = cy + radius * sin(angle);
        float x2 = cx + (radius + 20) * cos(angle); // Length of rays
        float y2 = cy + (radius + 20) * sin(angle);

        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sun at the center of the window with radius 50
    drawSun(320, 240, 50);

    glFlush();
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Background color: white
    glColor3f(0.0f, 0.0f, 0.0f); // Drawing color: black
    glPointSize(4.0); // Point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Sun Drawing");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
