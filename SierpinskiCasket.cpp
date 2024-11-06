#include <GL/freeglut.h>
#include <stdlib.h>

struct glIntPoint {
    GLint x;
    GLint y;
};

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1920, 0, 1080);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sierpinski Casket
    glIntPoint initPoints[3] = {{240,135},{1680,135},{960,945}};

    int index = rand() % 3;
    glIntPoint point = initPoints[index];

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
        glVertex2i(point.x,point.y);
        for (int i = 0; i < 80000 ; i++){
            index = rand() % 3;
            point.x = (point.x + initPoints[index].x) / 2;
            point.y = (point.y + initPoints[index].y) / 2;
            glVertex2i(point.x,point.y);
        }
    glEnd();
    glutSwapBuffers();
    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);   
    glutCreateWindow("Sierpinski Casket");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}