#include <windows.h> // use proper includes for your system
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

// Define control points for the Bézier curve
struct Point {
    float x, y;
};

Point controlPoints[4] = {
    { -0.8f, -0.8f },  // First control point
    { -0.4f,  0.8f },  // second control point
    {  0.4f, -0.8f },  // third control point
    {  0.8f,  0.8f }   // Fourth control point
};

// Function to compute a point on a cubic Bézier curve
Point computeBezierPoint(float t, Point* cp) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Point p;
    p.x = uuu * cp[0].x; // (1-t)^3 * P0
    p.x += 3 * uu * t * cp[1].x; // 3 * (1-t)^2 * t * P1
    p.x += 3 * u * tt * cp[2].x; // 3 * (1-t) * t^2 * P2
    p.x += ttt * cp[3].x; // t^3 * P3

    p.y = uuu * cp[0].y;
    p.y += 3 * uu * t * cp[1].y;
    p.y += 3 * u * tt * cp[2].y;
    p.y += ttt * cp[3].y;

    return p;
}

// Function to draw the Bézier curve
void drawBezierCurve() {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float t = i / 100.0f; // t ranges from 0 to 1
        Point p = computeBezierPoint(t, controlPoints);
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with the set background color

    // Draw control points
    glPointSize(5.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();

    // Draw Bézier curve
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBezierCurve();

    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bezier Curve");

    // Set the background color to white before starting the main loop
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white

    glutDisplayFunc(display);

    // Set up the orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}
