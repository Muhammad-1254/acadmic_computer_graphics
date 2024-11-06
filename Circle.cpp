#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

const int screenHeight = 960;
const int screenWidth = 1280;

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
    float i = 0;
    
    float x = 100;
    float y = 0;

    float X,Y;

    while (i < 200){
        float j = i;
        float comp = j + 10;

        while (j < comp){

            X = x*cos(i), Y = y*sin(i);

            glBegin(GL_POINTS);
                glVertex2f(X+sin(j),Y+cos(j));
            glEnd();
            j ++;
        }

        glBegin(GL_POINTS);
            glVertex2f(x+cos(i),y+sin(i));
        glEnd();

        i += 0.314;
    }

    glutSwapBuffers();
}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    // glutInitWindowPosition(200,400);
    glutCreateWindow("Dot Plot of a Function:");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}