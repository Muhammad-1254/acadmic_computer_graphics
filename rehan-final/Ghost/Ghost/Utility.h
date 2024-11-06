#pragma once
#include <gl/freeglut.h>
#include <cmath>

class Utility {

public:

    static void drawCircle(float x, float y, float radius, int numSegments) {
        float angleStep = 2.0f * 3.14159f / numSegments;
		glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center of the circle

        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * angleStep;
            float dx = radius * cos(angle);
            float dy = radius * sin(angle);
            glVertex2f(x + dx, y + dy);
        }

        glEnd();
    }

	static void drawSemiCircle(float x, float y, float radius) {
		const int numSegments = 20; // Number of segments to approximate the circle
		float angleStep = 3.14159f / numSegments;

		// Color values
		float r = 1.0f, g = 1.0f, b = 1.0f; // Example color (red)

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(r, g, b); // Set the color of the circle

		// Center of the circle
		glVertex2f(x, y);

		for (int i = 0; i <= numSegments; ++i) {
			float angle = i * angleStep;
			float dx = radius * cos(angle);
			float dy = radius * sin(angle);
			glVertex2f(x + dx, y + dy);
		}

		glEnd();
	}

	static void drawRectangle(float x, float y, float width, float height) {
		// Color values
		float r = 1.0f, g = 1.0f, b = 1.0f; // Example color (green)

		glBegin(GL_QUADS);
		glColor3f(r, g, b); // Set the color of the rectangle

		// Define the four corners of the rectangle
		glVertex2f(x, y);                    // Bottom-left
		glVertex2f(x + width, y);            // Bottom-right
		glVertex2f(x + width, y + height);   // Top-right
		glVertex2f(x, y + height);           // Top-left

		glEnd();
	}

	static void draw(float ghostX , float ghostY) {
		drawSemiCircle(ghostX, ghostY, 50);
		drawRectangle(ghostX - 50, ghostY - 100, 100, 100);
		drawCircle(ghostX-20,ghostY,15,40);
		drawCircle(ghostX + 20, ghostY, 15, 40);
	}
};