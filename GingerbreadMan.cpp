#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

const int screenHeight = 960;
const int screenWidth = 1280;

const int M = 40;
const int L = 3;

float p[2];

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glPointSize(2.0);
    glColor3f(0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1280.0f,(GLdouble)screenWidth,-960.0f,(GLdouble)screenHeight);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 200000; i ++){
        float x = M * (1 + 2*L) - p[1] + abs(p[0]-L*M);
        float y = p[0];
    
        glBegin(GL_POINTS);
            glVertex2f(x,y);
        glEnd();

        p[0] = x; p[1] = y;
    }
    glutSwapBuffers();
}

int main(int argc, char** argv){
    
    std::cout << "\nEnter x coordinate: ";
    std::cin >> p[0];

    std::cout << "\nEnter y coordinate: ";
    std::cin >> p[1];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(200,400);
    glutCreateWindow("Dot Plot of a Function:");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}