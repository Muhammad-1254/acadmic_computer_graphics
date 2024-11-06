#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

const int screenWidth = 640;
const int screenHeight = 480;

GLdouble A, V, C, D;

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);
    A = screenWidth / 4.0;
    V = 0.0;
    C = D = screenHeight / 2.0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
        for(GLdouble x = 0; x < 4.0; x += 0.005){
            GLdouble func = exp(-fabs(x)) * cos(2* 3.1459268 * x);
            glVertex2d(A*x + V, C * func + D);
        }
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Dot Plot of a Function:");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}