#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

const int screenWidth = 640;
const int screenHeight = 480;

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_LOOP);
        glVertex2i(40,40);
        glVertex2i(40,90);
        glVertex2i(70,120);
        glVertex2i(100,90);
        glVertex2i(100,40);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2i(50,100);
        glVertex2i(50,120);
        glVertex2i(60,120);
        glVertex2i(60,110);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2i(50,40);
        glVertex2i(50,75);
        glVertex2i(70,75);
        glVertex2i(70,40);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2i(80,70);
        glVertex2i(80,80);
        glVertex2i(90,80);
        glVertex2i(90,70);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("A Hard Wired House:");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}