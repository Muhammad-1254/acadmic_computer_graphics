#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

// Constants for hexagon properties
const float hexRadius = 0.1f;
const int numHexagonsX = 10;
const int numHexagonsY = 5;

void drawHexagon(float centerX, float centerY) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 6; i++) {
        float angle = 2.0f * 3.142 * i / 6.0f; 
        float x = centerX + hexRadius * cos(angle);
        float y = centerY + hexRadius * sin(angle);
        glVertex2f(x, y);
    } 
    glEnd();
}

void tileHexagons() {
    
    for (int i = 0; i < numHexagonsX; i++) {
        for (int j = 0; j < numHexagonsY; j++) {
            float xOffset = i * (3.0f * hexRadius)/2; // Horizontal spacing
            float yOffset = j * sqrt(3.0f) * hexRadius; // Vertical spacing

            if (i % 2 != 0) {
                yOffset += sqrt(3.0f) / 2.0f * hexRadius; // Adjust for odd columns
            }

            drawHexagon(xOffset , yOffset); 
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    tileHexagons(); 
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 2.0, -1.0, 2.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 1000);
    glutCreateWindow("Hexagon Tiling");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
