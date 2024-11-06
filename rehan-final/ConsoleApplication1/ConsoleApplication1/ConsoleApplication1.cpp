#include <GL/glut.h>
#include <stdlib.h>

// Define the coordinates of the Big Dipper stars in the range [0, 799]
struct Star {
    GLint x;
    GLint y;
};

Star bigDipperStars[] = {
    {130, 300}, // Dubhe
    {240, 355}, // Merak
    {320, 335}, // Phecda
    {430, 325}, // Megrez
    {600, 415}, // Alioth
    {625, 320}, // Mizar
    {465, 280}  // Alkaid
};

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 799.0, 0.0, 599.0); // Set the coordinate system to match the star coordinates
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw lines connecting the stars
    glColor3f(0.0f, 1.0f, 0.0f); // Set line color to light blue
    glBegin(GL_LINES);
    // Connect stars to form the Big Dipper
    glVertex2i(bigDipperStars[0].x, bigDipperStars[0].y); // Alkaid
    glVertex2i(bigDipperStars[1].x, bigDipperStars[1].y); // Mizar
    glVertex2i(bigDipperStars[1].x, bigDipperStars[1].y); // Mizar
    glVertex2i(bigDipperStars[2].x, bigDipperStars[2].y); // Alioth
    glVertex2i(bigDipperStars[2].x, bigDipperStars[2].y); // Alioth
    glVertex2i(bigDipperStars[3].x, bigDipperStars[3].y); // Megrez
    glVertex2i(bigDipperStars[3].x, bigDipperStars[3].y); // Megrez
    glVertex2i(bigDipperStars[4].x, bigDipperStars[4].y); // Phecda
    glVertex2i(bigDipperStars[4].x, bigDipperStars[4].y); // Phecda
    glVertex2i(bigDipperStars[5].x, bigDipperStars[5].y); // Dubhe
    glVertex2i(bigDipperStars[5].x, bigDipperStars[5].y); // Dubhe
    glVertex2i(bigDipperStars[6].x, bigDipperStars[6].y); // Merak
    glVertex2i(bigDipperStars[6].x, bigDipperStars[6].y); // Merak
    glVertex2i(bigDipperStars[3].x, bigDipperStars[3].y); // Megrez
    glEnd();

    // Draw stars
    glColor3f(1.0f, 1.0f, 1.0f); // Set star color to white
    glBegin(GL_POINTS);
    for (int i = 0; i < 7; ++i) {
        glVertex2i(bigDipperStars[i].x, bigDipperStars[i].y);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Adjusted window size to match coordinate range
    glutCreateWindow("The Big Dipper");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
