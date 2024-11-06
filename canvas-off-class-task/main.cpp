#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

class Point2 {
public:
    Point2() { x = y = 0.0f; }
    Point2(float xx, float yy) { x = xx; y = yy; }
    void set(float xx, float yy) { x = xx; y = yy; }
    float getX() { return x; }
    float getY() { return y; }
    void draw(void) {
        glBegin(GL_POINTS);
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }
private:
    float x, y;
};

class IntRect {
public:
    IntRect() { l = 0; r = 100; b = 0; t = 100; }
    IntRect(int left, int right, int bottom, int top) { l = left; r = right; b = bottom; t = top; }
    void set(int left, int right, int bottom, int top) { l = left; r = right; b = bottom; t = top; }
    void draw(void) {
        glBegin(GL_LINE_LOOP);
        glVertex2i(l, b);
        glVertex2i(r, b);
        glVertex2i(r, t);
        glVertex2i(l, t);
        glEnd();
    }
private:
    int l, r, b, t;
};

class RealRect {
public:
    RealRect() { l = 0; r = 100; b = 0; t = 100; }
    RealRect(float left, float right, float bottom, float top) { l = left; r = right; b = bottom; t = top; }
    void set(float left, float right, float bottom, float top) { l = left; r = right; b = bottom; t = top; }
    void draw(void) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(l, b);
        glVertex2f(r, b);
        glVertex2f(r, t);
        glVertex2f(l, t);
        glEnd();
    }
private:
    float l, r, b, t;
};

class Canvas {
public:
    Canvas(int width, int height, char* windowTitle) {
        char* argv[1];
        char dummyString[8];
        argv[0] = dummyString;
        int argc = 1;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(20, 20);
        glutCreateWindow(windowTitle);
        setWindow(0, (float)width, 0, (float)height);
        setViewport(0, width, 0, height);
        CP.set(0.0f, 0.0f);
    }

    void setWindow(float l, float r, float b, float t) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(l, r, b, t);
    }

    void setViewport(int l, int r, int b, int t) {
        glViewport(l, b, r - l, t - b);
    }

    void clearScreen() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void setBackgroundColor(float r, float g, float b) {
        glClearColor(r, g, b, 0.0);
    }

    void setColor(float r, float g, float b) {
        glColor3f(r, g, b);
    }

    void moveTo(float x, float y) {
        CP.set(x, y);
    }

    void lineTo(float x, float y) {
        glBegin(GL_LINES);
        glVertex2f(CP.getX(), CP.getY());
        glVertex2f(x, y);
        glEnd();
        CP.set(x, y);
    }

private:
    Point2 CP;
};

Canvas* canvas;

void display() {
    canvas->clearScreen();

    // Set background color to light blue
     //r: 173, g : 216, b : 230
    canvas->setBackgroundColor(0.678f, 0.847f, 0.902f);  
    glClear(GL_COLOR_BUFFER_BIT);

    // Task 1: Drawing points
    canvas->setColor(1.0f, 0.0f, 0.0f);  
    Point2 p1(50, 50), p2(100, 100), p3(150, 150);
    p1.draw();
    p2.draw();
    p3.draw();

    // Task 2: Drawing rectangles
    canvas->setColor(0.0f, 1.0f, 0.0f);  
    IntRect intRect(50, 200, 50, 200);
    intRect.draw();

    RealRect realRect(150.5f, 300.5f, 150.5f, 300.5f);
    realRect.draw();

    // Task 3: Draw diagonal line from (0, 0) to (400, 400)
    canvas->setColor(0.0f, 0.0f, 0.0f);  // Black
    canvas->moveTo(0.0f, 0.0f);
    canvas->lineTo(400.0f, 400.0f);

    // Task 5: Custom shapes (e.g., triangle, another rectangle, circle)
    // Triangle
    canvas->setColor(0.5f, 0.5f, 0.0f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(10.0f, 250.0f);
    glVertex2f(120.0f, 250.0f);
    glVertex2f(55.0f, 300.0f);
    glEnd();

    // Another rectangle
    canvas->setColor(0.0f, 0.5f, 0.5f);  
    RealRect customRect(100.0f, 200.0f, 300.0f, 350.0f);
    customRect.draw();
    //drawCircle(canvas, 200.0f, 200.0f, 50.0f);

    // Circle
    glBegin(GL_POLYGON);  
    const int numSegments = 100;  
    float angleIncrement = 2.0f * 3.14159f / numSegments;
    float centerX = 300.0f;
    float centerY = 100.0f;
    float radius = 50.0f;
    canvas->setColor(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < numSegments; ++i) {
        float angle = i * angleIncrement;
        float x = centerX + radius * cos(angle);  
        float y = centerY + radius * sin(angle);  
        glVertex2f(x, y);  
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    canvas = new Canvas(400, 400, (char*)"Geometric Shapes");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
