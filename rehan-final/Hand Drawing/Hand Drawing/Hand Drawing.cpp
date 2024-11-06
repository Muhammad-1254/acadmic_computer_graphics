#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

const int screenWidth = 1200;
const int screenHeight = 900;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)80, 0.0, (GLdouble)60);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // VLUE SKIYE
    // glColor3f(0.68f, 0.85f, 0.90f);
    glColor3f(0.0f, 0.75f, 0.75f);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(0, 60);
    glVertex2i(80, 60);
    glVertex2i(80, 0);
    glVertex2i(0, 0);
    glEnd();

    // Mountains
    glColor3f(0.71f, 0.53f, 0.39f);
    glBegin(GL_POLYGON);
    glVertex2i(0, 34);
    glVertex2i(0, 40);
    glVertex2i(10, 50);
    glVertex2i(24, 40);
    glVertex2f(44.0, 49.5);
    glVertex2i(58, 54);
    glVertex2i(80, 44);
    glVertex2i(80, 43);
    glVertex2i(0, 34);
    glEnd();

    glColor3f(0.59f, 0.41f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(12.5, 48.0);
    glVertex2i(25, 57);
    glVertex2i(38, 54);
    glVertex2i(36, 52);
    glVertex2i(30, 54);
    glVertex2i(18, 44);
    glVertex2f(12.5, 48.0);
    glEnd();

    glColor3f(0.65f, 0.48f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2i(18, 44);
    glVertex2i(30, 54);
    glVertex2i(44, 49);
    glVertex2i(24, 40);
    glVertex2i(18, 44);
    glEnd();

    glColor3f(0.65f, 0.45f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2i(35, 52);
    glVertex2i(44, 60);
    glVertex2f(48.0, 50.5);
    glVertex2i(44, 49);
    glVertex2i(35, 52);
    glEnd();

    glColor3f(0.59f, 0.41f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2i(58, 54);
    glVertex2f(48, 50.5);
    glVertex2i(46, 55);
    glVertex2i(56, 60);
    glVertex2i(69, 49);
    glVertex2i(58, 54);
    glEnd();

    // DARK GREEN GRASS
    glColor3f(0.0f, 0.39f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2i(0, 22);
    glVertex2i(0, 34);
    glVertex2i(80, 43);
    glVertex2i(80, 23);
    glVertex2i(0, 22);
    glEnd();

    // LIGHT GREEN GRASS
    glColor3f(0.5f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2i(0, 15);
    glVertex2i(0, 22);
    glVertex2i(80, 25);
    glVertex2i(80, 16);
    glVertex2i(0, 15);
    glEnd();

    //PATH
    glColor3f(0.96f, 0.64f, 0.38f);
    glBegin(GL_POLYGON);
    glVertex2i(37, 18);
    glVertex2i(29, 19);
    glVertex2i(32, 20);
    glVertex2i(38, 19);
    glVertex2i(44, 22);
    glVertex2i(46, 21);
    glVertex2i(40, 18);
    glVertex2f(41.0, 15.5);
    glVertex2f(35.0, 15.5);
    glVertex2i(37, 18);
    glEnd();

    // H1 - RIGHT WALL
    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(28.0, 18.55);
    glVertex2i(28, 25);
    glVertex2f(33.0, 26.5);
    glVertex2f(33.0, 20.45);
    glVertex2f(28.0, 18.55);
    glEnd();

    // H1 - DOOR
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2i(29, 19);
    glVertex2i(29, 24);
    glVertex2i(32, 25);
    glVertex2i(32, 20);
    glVertex2i(29, 19);
    glEnd();

    // H1 - LEFT WALL
    glColor3f(0.65f, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2i(20, 21);
    glVertex2i(20, 25);
    glVertex2i(28, 25);
    glVertex2f(28.0, 18.5);
    glVertex2i(20, 21);
    glEnd();

    // H1 - LEFT ROOF
    glColor3f(0.55f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2i(20, 25);
    glVertex2i(22, 29);
    glVertex2i(30, 30);
    glVertex2i(28, 25);
    glVertex2i(20, 25);
    glEnd();

    // H1 - RIGHT ROOF
    glColor3f(0.4f, 0.26f, 0.13f);
    glBegin(GL_POLYGON);
    glVertex2i(28, 25);
    glVertex2i(30, 30);
    glVertex2f(33.0, 26.5);
    glVertex2i(28, 25);
    glEnd();

    // H2 - LEFT WALL
    glColor3f(0.6f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(43, 22.5);
    glVertex2f(43, 29.5);
    glVertex2f(47.0, 27.5);
    glVertex2f(47.0, 20.5);
    glVertex2f(43, 22.5);
    glEnd();

    // H2 - DOOR
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(44.0, 22.0);
    glVertex2f(44.0, 27.5);
    glVertex2f(46.0, 26.5);
    glVertex2f(46.0, 21.0);
    glVertex2f(44.0, 22.0);
    glEnd();

    // H2 - RIGHT WALL
    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(47.0, 20.5);
    glVertex2f(47.0, 27.5);
    glVertex2f(54.5, 29.0);
    glVertex2f(54.5, 24.0);
    glVertex2f(47.0, 20.5);
    glEnd();

    // H2 - WINDOW
    glColor3f(0.5f, 0.7f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(49.0, 23.0);
    glVertex2f(49.0, 26.5);
    glVertex2f(52.5, 27.4);
    glVertex2f(52.5, 24.5);
    glVertex2f(49.0, 23.0);
    glEnd();

    // H2 - LEFT ROOF
    glColor3f(0.4f, 0.26f, 0.13f);
    glBegin(GL_POLYGON);
    glVertex2f(43.0, 29.5);
    glVertex2f(47.0, 27.5);
    glVertex2f(45.5, 32.0);
    glVertex2f(43.0, 29.5);
    glEnd();

    // H2 - RIGHT ROOF
    glColor3f(0.55f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(47.0, 27.5);
    glVertex2f(45.5, 32.0);
    glVertex2f(52.5, 32.3);
    glVertex2f(54.5, 29.0);
    glVertex2f(47.0, 27.5);
    glEnd();

    // TREE LEFT
    glColor3f(0.54f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(56.2, 24.1);
    glVertex2f(57.4, 29);
    glVertex2f(57.8, 24.2);
    glVertex2f(56.2, 24.1);
    glEnd();
    glColor3f(0.3f, 0.6f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(57.4, 29);
    glVertex2f(56.4, 28);
    glVertex2f(57.4, 33);
    glVertex2f(58.4, 28);
    glVertex2f(57.4, 29);
    glEnd();

    // TREE RIGHT
    glColor3f(0.54f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(58.2, 24.1);
    glVertex2f(59.4, 28);
    glVertex2f(59.8, 24.2);
    glVertex2f(58.2, 24.1);
    glEnd();
    glColor3f(0.3f, 0.6f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(59.4, 28);
    glVertex2f(58.4, 27);
    glVertex2f(59.4, 34);
    glVertex2f(60.4, 27);
    glVertex2f(59.4, 28);
    glEnd();


    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Hand Drawing:");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}