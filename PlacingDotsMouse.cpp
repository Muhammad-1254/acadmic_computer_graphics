#include <GL/freeglut.h>
// #include <iostream>

int screenHeight = 1080;
int screenWidth = 1920;
bool isDrawing = false;

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2d(x, screenHeight - y); // Flip y-coordinate
    glEnd();
    glFlush();
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDrawing = true;
            drawPoint(x, y);
        } else if (state == GLUT_UP) {
            isDrawing = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // Change background to red
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
}

void myMouseMotion(int x, int y) {
    if (isDrawing) {
        // std::cout << x << ", " << y << std::endl;
        drawPoint(x, y);
    }
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0); // Set point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
    glClear(GL_COLOR_BUFFER_BIT); // Clear once at the beginning
    glFlush();
}

void display() {
    // Leave empty, no need to clear or redraw anything
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Drawing Points with Mouse");

    init();

    glutMouseFunc(myMouse);
    glutMotionFunc(myMouseMotion);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
