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

void drawTriangle(float cx, float cy, float radius, float angle) {
    float newangle = angle * M_PI / 180;
    float nextAngle = (angle + 45) * M_PI / 180;

    // Points of the triangle
    float x1 = cx + (radius + 10) * cos(newangle);
    float y1 = cy + (radius + 10) * sin(newangle);

    float x2 = cx + (radius + 80) * cos(newangle + M_PI /12);
    float y2 = cy + (radius + 80) * sin(newangle+ M_PI /12);

    float x3 = cx + (radius + 10) * cos(nextAngle - M_PI / 12);
    float y3 = cy + (radius + 10) * sin(nextAngle - M_PI / 12);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawSun(float cx, float cy, float radius) {
    // Draw the circle (sun)
    drawCircle(cx, cy, radius);

    // Draw rays as triangles around the circle
    for (int i = 0; i < 8; i++) {
        float angle = i * 45; // 45 degrees between rays
        drawTriangle(cx, cy, radius, angle);
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sun at the center of the window with radius 100
    drawSun(320, 240, 100);

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
    glutCreateWindow("Sun Drawing with Triangular Rays");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
